import sys
import asyncio
from typing import Dict, Any
from prompt_toolkit import PromptSession, print_formatted_text
from prompt_toolkit.formatted_text import FormattedText
from prompt_toolkit.patch_stdout import patch_stdout

class FixedREPL:
    def __init__(self):
        try:
            self.session = PromptSession()
            self.colors_enabled = True
        except Exception:
            # Fallback to simple input if prompt_toolkit fails
            self.session = None
            self.colors_enabled = False

    async def safe_print(self, text):
        """Thread-safe printing that works with or without prompt_toolkit"""
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
                
                if "v" in message and "n" in message:
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
                full_output = "".join(output) + "\n"
                asyncio.create_task(self.safe_print(full_output))
            
            return True
            
        except Exception as e:
            error_msg = f"\nFormat error: {e}\n"
            asyncio.create_task(self.safe_print(error_msg))
            return False

async def main():
    repl = FixedREPL()
    
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
                
        except KeyboardInterrupt:
            continue
        except EOFError:
            break
        except Exception as e:
            error_msg = f"\nFatal error: {e}\n"
            asyncio.create_task(repl.safe_print(error_msg))
            break

if __name__ == "__main__":
    try:
        if sys.platform == "win32":
            asyncio.set_event_loop_policy(asyncio.WindowsSelectorEventLoopPolicy())
        asyncio.run(main())
    except KeyboardInterrupt:
        pass
    