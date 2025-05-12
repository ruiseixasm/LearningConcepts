from prompt_toolkit.application.current import get_app

def safe_print(*args, **kwargs):
    """Print that won't interfere with prompt display"""
    app = get_app()
    if app.is_running:
        print_formatted_text(*args, **kwargs)
    else:
        print(*args, **kwargs)
        