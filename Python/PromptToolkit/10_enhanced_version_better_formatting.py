import asyncio
from concurrent.futures import ThreadPoolExecutor
from queue import Queue, Empty
from prompt_toolkit import PromptSession, print_formatted_text
from prompt_toolkit.patch_stdout import patch_stdout
from prompt_toolkit.formatted_text import HTML, FormattedText

class AsyncREPL:
    def __init__(self):
        self.output_queue = Queue()
        self.executor = ThreadPoolExecutor()
        self.session = PromptSession()
    
    async def output_handler(self):
        """Handle all output printing"""
        while True:
            try:
                item = self.output_queue.get_nowait()
                if isinstance(item, FormattedText):
                    print_formatted_text(item)
                else:
                    print_formatted_text(HTML(item))
                self.output_queue.task_done()
            except Empty:
                await asyncio.sleep(0.05)
    
    def queue_output(self, content, style=None):
        """Thread-safe output queuing"""
        if style:
            self.output_queue.put(FormattedText([(style, content)]))
        else:
            self.output_queue.put(content)
    
    async def run_command(self, cmd):
        """Execute a command with progressive output"""
        if cmd == 'talk':
            def _execute():
                for i in range(5):
                    asyncio.run_coroutine_threadsafe(
                        asyncio.sleep(1), 
                        loop=asyncio.get_event_loop()
                    ).result()
                    self.queue_output(
                        f"[<ansired>Talker</ansired>] Update {i+1}/5\n",
                        "class:output"
                    )
            
            await asyncio.get_event_loop().run_in_executor(
                self.executor, 
                _execute
            )
    
    async def run(self):
        """Main REPL loop"""
        output_task = asyncio.create_task(self.output_handler())
        
        try:
            while True:
                with patch_stdout():
                    try:
                        user_input = await self.session.prompt_async(
                            HTML('<ansigreen>>>> </ansigreen>')
                        )
                        await self.run_command(user_input.strip())
                    except KeyboardInterrupt:
                        self.queue_output("^C\n")
                        continue
        finally:
            output_task.cancel()
            await output_task

if __name__ == "__main__":
    repl = AsyncREPL()
    asyncio.run(repl.run())
    