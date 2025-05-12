from prompt_toolkit import PromptSession
from prompt_toolkit.formatted_text import HTML

def get_prompt():
    # Return "..." if the previous line ends with ":"
    if buffer.text and buffer.text.rstrip().endswith(':'):
        return HTML('<ansigreen>... </ansigreen>')
    return HTML('<ansigreen>>>> </ansigreen>')

session = PromptSession()
buffer = session.default_buffer

while True:
    text = session.prompt(get_prompt, multiline=True)
    print('You entered:', text)
    