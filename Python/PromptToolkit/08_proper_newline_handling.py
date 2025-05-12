def talk_command():
    lines = [
        "[Talker-00]     A simple Talker!",
        "[Buzzer]        I do a 500ms buzz!"
    ]
    print_formatted_text(FormattedText([
        ('', '\n'.join(lines))
    ]))
    