from prompt_toolkit import PromptSession
from prompt_toolkit.formatted_text import HTML

session = PromptSession()

def handle_command(command):
    if command == 'talk':
        talk_command()
    # Add other commands here

while True:
    try:
        user_input = session.prompt(HTML('<ansigreen>>>> </ansigreen>'))
        handle_command(user_input.strip())
    except KeyboardInterrupt:
        continue
    except EOFError:
        break
    