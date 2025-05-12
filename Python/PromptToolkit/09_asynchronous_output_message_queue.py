import asyncio
from concurrent.futures import ThreadPoolExecutor
from queue import Queue, Empty
from prompt_toolkit import PromptSession
from prompt_toolkit.patch_stdout import patch_stdout
from prompt_toolkit.formatted_text import HTML

# Message queue for output
output_queue = Queue()

def long_running_command():
    """Simulate a command that takes time with progressive output"""
    import time
    for i in range(5):
        time.sleep(1)  # Simulate work
        output_queue.put(f"[Task] Progress update {i+1}/5\n")

async def display_output():
    """Coroutine that displays output from the queue"""
    while True:
        try:
            # Non-blocking queue check
            message = output_queue.get_nowait()
            # Print above the prompt
            print_formatted_text(message, end='')
            output_queue.task_done()
        except Empty:
            await asyncio.sleep(0.1)  # Yield control briefly

async def main():
    session = PromptSession()
    
    # Start output display task
    output_task = asyncio.create_task(display_output())
    
    while True:
        try:
            with patch_stdout():
                user_input = await session.prompt_async(HTML('<ansigreen>>>> </ansigreen>'))
            
            if user_input.strip() == 'talk':
                # Run blocking command in executor
                await asyncio.get_event_loop().run_in_executor(
                    None, 
                    long_running_command
                )
                
        except KeyboardInterrupt:
            continue
        except EOFError:
            break
    
    output_task.cancel()
    try:
        await output_task
    except asyncio.CancelledError:
        pass

if __name__ == "__main__":
    asyncio.run(main())
    