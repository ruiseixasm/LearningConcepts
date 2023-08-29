import pygame
from pygame.sprite import Sprite
import os # v.2 (my changes)

class Alien(Sprite):
    """A class to represent a single alien in the fleet."""

    def __init__(self, ai_game):
        """Initialize the alien and set its starting position."""
        super().__init__()
        self.screen = ai_game.screen
        self.settings = ai_game.settings # v.2

        # Load the alien image and set its rect attribute.
        self.dir_path = os.path.dirname(os.path.abspath(__file__)) # v.2 (my changes)
        image_path = os.path.join(self.dir_path, 'images\\alien.bmp') # v.2 (my changes)
        #print (f"Image path name: {image_path}") # v.2 (my changes)
        self.image = pygame.image.load(image_path) # v.2 (my changes)
        self.rect = self.image.get_rect()

        # Start each new alien near the top left of the screen.
        self.rect.x = self.rect.width
        self.rect.y = self.rect.height

        # Store the alien's exact horizontal position.
        self.x = float(self.rect.x)

    def check_edges(self): # v.2
        """Return True if alien is at edge of screen."""
        screen_rect = self.screen.get_rect()
        if self.rect.right >= screen_rect.right or self.rect.left <= 0:
            return True

    def update(self): # v.2
        """Move the alien to the right."""
        self.x += self.settings.alien_speed * self.settings.fleet_direction
        self.rect.x = self.x