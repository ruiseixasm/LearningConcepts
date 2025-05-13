import asyncio
from typing import Dict, Any
from prompt_toolkit import PromptSession, print_formatted_text
from prompt_toolkit.output import ColorDepth
from prompt_toolkit.patch_stdout import patch_stdout
from prompt_toolkit.formatted_text import FormattedText, HTML
from prompt_toolkit.output.defaults import create_output

class RobustREPL:
    def __init__(self):
        try:
            # Create a failsafe output
            self.output = create_output()
            self.session = PromptSession(
                output=self.output,
                color_depth=ColorDepth.TRUE_COLOR
            )
        except Exception as e:
            print(f"Error initializing terminal: {e}")
            # Fallback to basic output
            self.session = PromptSession()

    async def safe_print(self, content):
        """Thread-safe printing with error handling"""
        try:
            with patch_stdout():
                if isinstance(content, (FormattedText, HTML)):
                    print_formatted_text(content, output=self.output)
                else:
                    print(content, end='', flush=True)
        except Exception as e:
            print(f"\nOutput error: {e}\n", flush=True)

    def echo(self, message: Dict[str, Any]) -> bool:
        try:
            parts = []
            if "f" in message:
                parts.append(('[', '#888888'))
                parts.append((message["f"], '#00aa00'))
                
                if "w" in message:
                    what = {
                        0: "talk", 1: "list", 2: "run",
                        3: "set", 4: "get", 5: "sys"
                    }.get(message.get("w"), "echo")
                    
                    parts.append((f' {what}', '#0088ff'))
                    
                    if "n" in message:
                        parts.append((f' {message["n"]}', '#ff8800'))
                    
                    parts.append((']', '#888888'))
                    
                    # Handle value cases
                    value = None
                    if "v" in message and "n" in message:
                        value = str(message["v"])
                    elif "d" in message:
                        value = str(message["d"])
                    elif "r" in message:
                        value = str(message["r"])
                    elif "g" in message:
                        value = {
                            0: ("ROGER", '#00ff00'),
                            1: ("UNKNOWN", '#ffff00'),
                            2: ("NONE", '#ff0000')
                        }.get(message["g"], ("FAIL", '#ff0000'))
                        parts.append((f'\t{value[0]}', value[1]))
                    
                    if value and "g" not in message:
                        parts.append((f'\t{value}', ''))
                
                elif "d" in message:
                    parts.append((']', '#888888'))
                    parts.append((f'\t{message["d"]}', ''))
            
            if parts:
                asyncio.create_task(
                    self.safe_print(FormattedText(parts + [('\n', '')]))
                )
            
            return True
        
        except Exception as e:
            asyncio.create_task(
                self.safe_print(f"\nFormatting error: {e}\n")
            )
            return False

async def main():
    repl = RobustREPL()
    
    while True:
        try:
            with patch_stdout():
                user_input = await repl.session.prompt_async(
                    HTML('<ansigreen>>>> </ansigreen>')
                )
                
                # Process commands here
                if user_input.strip() == 'test':
                    repl.echo({
                        "f": "TestSystem",
                        "w": 5,
                        "n": "status",
                        "v": "Test message"
                    })
                    
        except KeyboardInterrupt:
            continue
        except EOFError:
            break
        except Exception as e:
            print(f"\nFatal error: {e}\n")
            break

if __name__ == "__main__":
    try:
        asyncio.run(main())
    except KeyboardInterrupt:
        pass
    