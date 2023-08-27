import sys
import pygame
from settings_2 import Settings
from ship_3 import Ship # v.7

class AlienInvasion:
    """Overall class to manage game assets and behavior."""

    def __init__(self):
        """Initialize the game, and create game resources."""
        pygame.init()
        self.settings = Settings()

        self.screen = pygame.display.set_mode(
            (self.settings.screen_width, self.settings.screen_height))
        pygame.display.set_caption("Alien Invasion")

        self.ship = Ship(self)

    def run_game(self):
        """Start the main loop for the game."""
        while True:
            # Refactoring into a method
            self._check_events() # v.4
            self.ship.update() # v.6
            self._update_screen() # v.4

    def _check_events(self): # v.4
        # Watch for keyboard and mouse events.
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                print("Close Button pressed!") # My Own code line
                sys.exit()
            elif event.type == pygame.KEYDOWN: # v.5
                self._check_keydown_events(event)
            elif event.type == pygame.KEYUP: # v.6
                self._check_keyup_events(event)

    def _check_keydown_events(self, event): # v.8
        """Respond to keypresses."""
        if event.key == pygame.K_RIGHT:
            # Move the ship to the right.
            self.ship.moving_right = True # v.6
        elif event.key == pygame.K_LEFT: # v.7
            # Move the ship to the right.
            self.ship.moving_left = True
        elif event.key == pygame.K_q:
            sys.exit()
        
    def _check_keyup_events(self, event): # v.8
        """Respond to keypresses."""
        if event.key == pygame.K_RIGHT:
            self.ship.moving_right = False
        if event.key == pygame.K_LEFT: # v.7
            self.ship.moving_left = False

    def _update_screen(self): # v.4
        # Redraw the screen during each pass through the loop.
        self.screen.fill(self.settings.bg_color)
        self.ship.blitme()

        # Make the most recently draw screen visible.
        pygame.display.flip()


if __name__ == '__main__':
    # Make a game instance, and run the game.
    ai = AlienInvasion()
    ai.run_game()