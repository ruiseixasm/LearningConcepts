import sys
import asyncio
import random
from typing import Dict, Any
from prompt_toolkit import PromptSession, print_formatted_text
from prompt_toolkit.formatted_text import FormattedText, HTML
from prompt_toolkit.patch_stdout import patch_stdout

class ColoredREPL:
    def __init__(self):
        try:
            self.session = PromptSession()
            self.colors_enabled = True
        except Exception:
            self.session = None
            self.colors_enabled = False
        
        self.simulating_events = False
        self.event_tasks = []
        self.max_prefix_length = 0
        self.color_map = {
            # Prefix colors by component
            "System": "ansicyan",
            "Sensor": "ansiyellow",
            "Network": "ansigreen",
            "Alert": "ansired",
            "Command": "ansiblue",
            "Debug": "ansimagenta",
            # Value colors by content
            "ROGER": "ansigreen",
            "FAIL": "ansired",
            "WARN": "ansiyellow",
            "ERROR": "ansired",
            "OK": "ansigreen",
            "Slow": "ansiyellow",
            "Timeout": "ansired"
        }

    async def safe_print(self, content):
        """Thread-safe printing with color support"""
        try:
            if self.session and self.colors_enabled:
                with patch_stdout():
                    if isinstance(content, (FormattedText, HTML)):
                        print_formatted_text(content)
                    else:
                        print(content, end='', flush=True)
            else:
                print(content, end='', flush=True)
        except Exception:
            print(content, end='', flush=True)

    def get_value_color(self, value: str) -> str:
        """Determine color for value based on content"""
        value_str = str(value)
        for pattern, color in self.color_map.items():
            if pattern in value_str:
                return color
        return ""  # Default no color

    def generate_formatted_output(self, message: Dict[str, Any]) -> FormattedText:
        """Generate color-formatted output with alignment"""
        parts = []
        prefix_parts = []
        
        # Build prefix with color
        if "f" in message:
            component = message["f"]
            prefix_color = self.color_map.get(component, "")
            
            prefix_parts.append(f"[{component}")
            
            if "w" in message:
                what = {
                    0: "talk", 1: "list", 2: "run",
                    3: "set", 4: "get", 5: "sys"
                }.get(message.get("w"), "echo")
                prefix_parts.append(f" {what}")
                
                if "n" in message:
                    prefix_parts.append(f" {message['n']}")
            
            prefix_parts.append("]")
            
            prefix = "".join(prefix_parts)
            if len(prefix) > self.max_prefix_length:
                self.max_prefix_length = len(prefix)
                
            if prefix_color:
                parts.append((prefix_color, prefix.ljust(self.max_prefix_length)))
            else:
                parts.append(('', prefix.ljust(self.max_prefix_length)))
        
        # Add separator
        parts.append(('', '\t'))
        
        # Build value with color
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
        
        if value:
            value_color = self.get_value_color(value)
            if value_color:
                parts.append((value_color, value))
            else:
                parts.append(('', value))
        
        return FormattedText(parts)

    def echo(self, message: Dict[str, Any]) -> bool:
        try:
            formatted_output = self.generate_formatted_output(message)
            asyncio.create_task(self.safe_print(formatted_output))
            return True
        except Exception as e:
            error_msg = FormattedText([('ansired', f"\nFormat error: {e}")])
            asyncio.create_task(self.safe_print(error_msg))
            return False

    async def simulate_random_event(self):
        """Generate random colored events"""
        event_types = [
            {"f": "Sensor", "w": 4, "n": "temp", "v": f"{random.randint(20, 30)}°C"},
            {"f": "Network", "w": 5, "n": "status", "v": random.choice(["OK", "Slow", "Timeout"])},
            {"f": "System", "w": 5, "v": random.choice(["CPU 45%", "RAM 60%", "Disk 85%"])},
            {"f": "Alert", "w": 0, "v": random.choice(["Motion detected", "Door opened", "Low battery"])},
            {"f": "Debug", "w": 5, "n": "level", "v": random.choice(["INFO", "WARN", "ERROR"])},
            {"f": "Command", "w": 5, "g": random.choice([0, 1, 2])}  # For ROGER/FAIL status
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
            self.echo({
                "f": "System", 
                "w": 5, 
                "v": "Event simulation started"
            })

    async def stop_event_simulation(self):
        """Stop the event simulation"""
        if self.simulating_events:
            self.simulating_events = False
            for task in self.event_tasks:
                task.cancel()
            self.event_tasks = []
            self.echo({
                "f": "System", 
                "w": 5, 
                "v": "Event simulation stopped"
            })

async def main():
    repl = ColoredREPL()
    await repl.start_event_simulation()
    
    while True:
        try:
            if repl.session:
                with patch_stdout():
                    user_input = await repl.session.prompt_async(HTML('<ansigreen>>>> </ansigreen>'))
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

if __name__ == "__main__":
    try:
        if sys.platform == "win32":
            asyncio.set_event_loop_policy(asyncio.WindowsSelectorEventLoopPolicy())
        asyncio.run(main())
    except KeyboardInterrupt:
        pass
    