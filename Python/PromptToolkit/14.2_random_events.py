import sys
import asyncio
import random
from typing import Dict, Any
from prompt_toolkit import PromptSession, print_formatted_text
from prompt_toolkit.formatted_text import FormattedText
from prompt_toolkit.patch_stdout import patch_stdout

class AlignedREPL:
    def __init__(self):
        try:
            self.session = PromptSession()
            self.colors_enabled = True
        except Exception:
            self.session = None
            self.colors_enabled = False
        
        self.simulating_events = False
        self.event_tasks = []
        self.max_prefix_length = 22  # Track maximum prefix length for alignment

    async def safe_print(self, text):
        """Thread-safe printing"""
        try:
            if self.session and self.colors_enabled:
                with patch_stdout():
                    print_formatted_text(FormattedText([('', text)]))
            else:
                print(text, end='', flush=True)
        except Exception:
            print(text, end='', flush=True)

    def generate_prefix(self, message: Dict[str, Any]) -> str:
        """Generate the prefix part with consistent formatting"""
        parts = []
        if "f" in message:
            parts.append(f"[{message['f']}")
            
            if "w" in message:
                what = {
                    0: "talk", 1: "list", 2: "run",
                    3: "set", 4: "get", 5: "sys"
                }.get(message.get("w"), "echo")
                parts.append(f" {what}")
                
                if "n" in message:
                    parts.append(f" {message['n']}")
            
            parts.append("]")
        
        prefix = "".join(parts)
        
        # Update max prefix length if this one is longer
        if len(prefix) > self.max_prefix_length:
            self.max_prefix_length = len(prefix)
        
        return prefix

    def echo(self, message: Dict[str, Any]) -> bool:
        try:
            prefix = self.generate_prefix(message)
            
            # Pad the prefix to the maximum length we've seen
            padded_prefix = prefix.ljust(self.max_prefix_length)
            
            # Handle the value part
            value = ""
            if "v" in message:
                value = str(message["v"])
            elif "d" in message:
                value = str(message["d"])
            elif "r" in message:
                value = str(message["r"])
            elif "g" in message:
                value = {
                    0: "ROGER", 1: "UNKNOWN", 2: "NONE"
                }.get(message["g"], "FAIL")
            
            # Combine into final output
            full_output = f"{padded_prefix}\t{value}"
            asyncio.create_task(self.safe_print(full_output))
            
            return True
            
        except Exception as e:
            error_msg = f"\nFormat error: {e}"
            asyncio.create_task(self.safe_print(error_msg))
            return False

    async def simulate_random_event(self):
        """Generate random simulated events with aligned output"""
        event_types = [
            {"f": "Sensor", "w": 4, "n": "temp", "v": f"{random.randint(20, 30)}°C"},
            {"f": "Network", "w": 5, "n": "status", "v": random.choice(["OK", "Slow", "Timeout"])},
            {"f": "System", "w": 5, "v": random.choice(["CPU 45%", "RAM 60%", "Disk 85%"])},
            {"f": "Alert", "w": 0, "v": random.choice(["Motion detected", "Door opened", "Low battery"])},
            {"f": "Command", "w": 5, "v": "Processing complete"},
            {"f": "Debug", "w": 5, "n": "level", "v": random.choice(["INFO", "WARN", "ERROR"])}
        ]
        
        while self.simulating_events:
            await asyncio.sleep(random.uniform(1.0, 3.0))
            event = random.choice(event_types)
            self.echo(event)

    async def start_event_simulation(self):
        """Start the event simulation"""
        if not self.simulating_events:
            self.simulating_events = True
            task = asyncio.create_task(self.simulate_random_event())
            self.event_tasks.append(task)
            self.echo({"f": "System", "w": 5, "v": "Event simulation started"})

    async def stop_event_simulation(self):
        """Stop the event simulation"""
        if self.simulating_events:
            self.simulating_events = False
            for task in self.event_tasks:
                task.cancel()
            self.event_tasks = []
            self.echo({"f": "System", "w": 5, "v": "Event simulation stopped"})

async def main():
    repl = AlignedREPL()
    
    # Start event simulation automatically
    await repl.start_event_simulation()
    
    while True:
        try:
            if repl.session:
                with patch_stdout():
                    user_input = await repl.session.prompt_async(">>> ")
            else:
                user_input = input(">>> ")
            
            if user_input.strip() == 'test':
                repl.echo({
                    "f": "TestSystem",
                    "w": 5,
                    "n": "status",
                    "v": "Test message"
                })
            elif user_input.strip() == 'start events':
                await repl.start_event_simulation()
            elif user_input.strip() == 'stop events':
                await repl.stop_event_simulation()
            elif user_input.strip() == 'exit':
                await repl.stop_event_simulation()
                break
            else:
                repl.echo({
                    "f": "Command",
                    "w": 5,
                    "v": f"Executed: {user_input}"
                })
                
        except KeyboardInterrupt:
            continue
        except EOFError:
            await repl.stop_event_simulation()
            break
        except Exception as e:
            error_msg = f"\nFatal error: {e}"
            asyncio.create_task(repl.safe_print(error_msg))
            await repl.stop_event_simulation()
            break

if __name__ == "__main__":
    try:
        if sys.platform == "win32":
            asyncio.set_event_loop_policy(asyncio.WindowsSelectorEventLoopPolicy())
        asyncio.run(main())
    except KeyboardInterrupt:
        pass
