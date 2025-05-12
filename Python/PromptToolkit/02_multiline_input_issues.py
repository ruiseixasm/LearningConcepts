from prompt_toolkit import PromptSession
from prompt_toolkit.lexers import PygmentsLexer
from pygments.lexers.python import PythonLexer

session = PromptSession(lexer=PygmentsLexer(PythonLexer))

while True:
    try:
        text = session.prompt(multiline=True)
        print('You entered:', text)
    except KeyboardInterrupt:
        continue
    except EOFError:
        break
    