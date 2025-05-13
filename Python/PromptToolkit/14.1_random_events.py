import sys
import asyncio
import random
from typing import Dict, Any
from prompt_toolkit import PromptSession, print_formatted_text
from prompt_toolkit.formatted_text import FormattedText
from prompt_toolkit.patch_stdout import patch_stdout

class EventSimulatingREPL:
    def __init__(self):
        try:
            self.session = PromptSession()
            self.colors_enabled = True
        except Exception:
            self.session = None
            self.colors_enabled = False
        
        # Event simulation control
        self.simulating_events = False
        self.event_tasks = []

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

    def echo(self, message: Dict[str, Any]) -> bool:
        try:
            output = []
            if "f" in message:
                output.append(f"[{message['f']}")
                
                if "w" in message:
                    what = {
                        0: "talk", 1: "list", 2: "run",
                        3: "set", 4: "get", 5: "sys"
                    }.get(message.get("w"), "echo")
                    output.append(f" {what}")
                    
                    if "n" in message:
                        output.append(f" {message['n']}")
                
                output.append("]")
                
                if "v" in message:
                    output.append(f"\t{message['v']}")
                elif "d" in message:
                    output.append(f"\t{message['d']}")
                elif "r" in message:
                    output.append(f"\t{message['r']}")
                elif "g" in message:
                    roger = {
                        0: "ROGER", 1: "UNKNOWN", 2: "NONE"
                    }.get(message["g"], "FAIL")
                    output.append(f"\t{roger}")
            
            if output:
                full_output = "".join(output)
                asyncio.create_task(self.safe_print(full_output))
            
            return True
            
        except Exception as e:
            error_msg = f"\nFormat error: {e}"
            asyncio.create_task(self.safe_print(error_msg))
            return False

    async def simulate_random_event(self):
        """Generate random simulated events"""
        event_types = [
            {"f": "Sensor", "w": 4, "n": "temp", "v": f"{random.randint(20, 30)}°C"},
            {"f": "Network", "w": 5, "n": "status", "v": random.choice(["OK", "Slow", "Timeout"])},
            {"f": "System", "w": 5, "v": random.choice(["CPU 45%", "RAM 60%", "Disk 85%"])},
            {"f": "Alert", "w": 0, "v": random.choice(["Motion detected", "Door opened", "Low battery"])}
        ]
        
        while self.simulating_events:
            await asyncio.sleep(random.uniform(1.0, 3.0))  # Random delay
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
    repl = EventSimulatingREPL()
    
    # Start event simulation automatically
    await repl.start_event_simulation()
    
    while True:
        try:
            if repl.session:
                with patch_stdout():
                    user_input = await repl.session.prompt_async(">>> ")
            else:
                user_input = input(">>> ")
            
            # Process user commands
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
            error_msg = f"\nFatal error: {e}\n"
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
    