async def main_repl_loop():
    repl = YourREPL()
    session = PromptSession()
    
    # Start output handler
    output_task = asyncio.create_task(repl.output_handler())
    
    try:
        while True:
            try:
                # Get user input
                with patch_stdout():
                    user_input = await session.prompt_async(HTML('<ansigreen>>>> </ansigreen>'))
                
                # Process command (example)
                if user_input.strip() == 'test':
                    # Example message that would come from your system
                    repl.echo({
                        "f": "System",
                        "w": 5,  # sys
                        "n": "status",
                        "v": "All systems operational"
                    })
                    
                    # Simulate delayed output
                    await asyncio.sleep(1)
                    repl.echo({
                        "f": "Sensor",
                        "w": 4,  # get
                        "n": "temp1",
                        "r": "23.5°C"
                    })
                    
            except KeyboardInterrupt:
                continue
            except EOFError:
                break
    finally:
        output_task.cancel()
        try:
            await output_task
        except asyncio.CancelledError:
            pass

if __name__ == "__main__":
    asyncio.run(main_repl_loop())
    