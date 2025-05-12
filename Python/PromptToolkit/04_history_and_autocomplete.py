from prompt_toolkit import PromptSession
from prompt_toolkit.history import FileHistory
from prompt_toolkit.completion import WordCompleter

completer = WordCompleter(['print', 'import', 'def', 'class'])
session = PromptSession(history=FileHistory('.repl-history'), completer=completer)

while True:
    text = session.prompt('>>> ')
    print('You entered:', text)

    