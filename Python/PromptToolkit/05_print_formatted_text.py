from prompt_toolkit import print_formatted_text
from prompt_toolkit.formatted_text import FormattedText

def talk_command():
    output = FormattedText([
        ('#ansigreen', '[Talker-00]    '),
        ('', 'A simple Talker!\n'),
        ('#ansigreen', '[Buzzer]       '),
        ('', 'I do a 500ms buzz!')
    ])
    print_formatted_text(output)
    