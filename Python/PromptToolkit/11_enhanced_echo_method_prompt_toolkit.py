from prompt_toolkit import print_formatted_text
from prompt_toolkit.formatted_text import FormattedText, HTML
from typing import Dict, Any
import asyncio
from queue import Queue

class YourREPL:
    def __init__(self):
        self.output_queue = Queue()
        
    async def output_handler(self):
        """Async task to handle output printing"""
        while True:
            try:
                message = self.output_queue.get_nowait()
                if isinstance(message, (FormattedText, HTML)):
                    print_formatted_text(message)
                else:
                    print(message, end='')
                self.output_queue.task_done()
            except Empty:
                await asyncio.sleep(0.05)
    
    def queue_output(self, content):
        """Thread-safe output queuing"""
        self.output_queue.put(content)
    
    def echo(self, message: Dict[str, Any]) -> bool:
        output_parts = []
        
        # Start with the tab and frame
        if "f" in message:
            output_parts.append(('[', '#888888'))  # Gray color for brackets
            output_parts.append((message["f"], '#00aa00'))  # Green for frame name
            
            # Handle the what/type part
            if "w" in message:
                what = "echo"
                if isinstance(message["w"], int) and 0 <= message["w"] <= 6:
                    what = {
                        0: "talk",
                        1: "list",
                        2: "run",
                        3: "set",
                        4: "get",
                        5: "sys"
                    }.get(message["w"], "echo")
                
                # Build the rest of the output
                output_parts.append((' ' + what, '#0088ff'))  # Blue for command type
                
                if "n" in message:
                    output_parts.append((' ' + str(message["n"]), '#ff8800'))  # Orange for name
                
                output_parts.append((']', '#888888'))  # Gray closing bracket
                
                # Handle value cases
                if "v" in message and "n" in message:
                    output_parts.append(('\t' + str(message["v"]), ''))
                elif "n" in message and "d" in message:
                    output_parts.append(('\t' + str(message["d"]), ''))
                elif "n" in message and "r" in message:
                    output_parts.append(('\t' + str(message["r"]), ''))
                elif "r" in message:
                    output_parts.append(('\t' + str(message["r"]), ''))
                elif "g" in message:
                    roger = {
                        0: ("ROGER", '#00ff00'),  # Green for success
                        1: ("UNKNOWN", '#ffff00'), # Yellow for unknown
                        2: ("NONE", '#ff0000')    # Red for failure
                    }.get(message["g"], ("FAIL", '#ff0000'))
                    
                    output_parts.append(('\t' + roger[0], roger[1]))
            
            elif "d" in message:
                output_parts.append((']', '#888888'))
                output_parts.append(('\t' + str(message["d"]), ''))
        
        # Convert to FormattedText and queue it
        if output_parts:
            # Add newline at the end
            output_parts.append(('\n', ''))
            formatted_output = FormattedText(output_parts)
            self.queue_output(formatted_output)
        
        return True
    