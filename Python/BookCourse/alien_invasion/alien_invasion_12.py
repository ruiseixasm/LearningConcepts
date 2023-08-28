import sys
import pygame
from settings_4 import Settings #v.12
from ship_3 import Ship # v.7
from bullet import Bullet # v.11

class AlienInvasion:
    """Overall class to manage game assets and behavior."""

    def __init__(self):
        """Initialize the game, and create game resources."""
        pygame.init()
        self.settings = Settings()

        # display=0 (Asus) | display=1 (Lenovo)
        self.screen = pygame.display.set_mode((0, 0), pygame.FULLSCREEN, display=0) # v.10
        self.settings.screen_width = self.screen.get_rect().width # v.9
        self.settings.screen_height = self.screen.get_rect().height # v.9
        pygame.display.set_caption("Alien Invasion")

        self.ship = Ship(self)
        self.bullets = pygame.sprite.Group() # v.11

    def run_game(self):
        """Start the main loop for the game."""
        while True:
            # Refactoring into a method
            self._check_events() # v.4
            self.ship.update() # v.6
            self.bullets.update() # v.11
            self._update_screen() # v.4

            # Get rid of bullets that have disappeared.
            for bullet in self.bullets: # v.12 (no need for .copy())
                if bullet.rect.bottom <= 0:
                    self.bullets.remove(bullet)
            print(len(self.bullets)) # v.12

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
        elif event.key == pygame.K_q or event.key == pygame.K_ESCAPE: # v.10
            sys.exit()
        elif event.key == pygame.K_SPACE: # v.11
            self._fire_bullet()
        
    def _check_keyup_events(self, event): # v.8
        """Respond to keypresses."""
        if event.key == pygame.K_RIGHT:
            self.ship.moving_right = False
        if event.key == pygame.K_LEFT: # v.7
            self.ship.moving_left = False

    def _fire_bullet(self): # v.11
        """Create a new bullet and add it to the bullets group."""
        if len(self.bullets) < self.settings.bullets_allowed: # v.12
            new_bullet = Bullet(self)
            self.bullets.add(new_bullet)

    def _update_screen(self): # v.4
        # Redraw the screen during each pass through the loop.
        self.screen.fill(self.settings.bg_color)
        self.ship.blitme()
        for bullet in self.bullets.sprites(): # v.11
            bullet.draw_bullet()

        # Make the most recently draw screen visible.
        pygame.display.flip()


if __name__ == '__main__':
    # Make a game instance, and run the game.
    ai = AlienInvasion()
    ai.run_game()