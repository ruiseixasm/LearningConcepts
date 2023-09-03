import pygame
from pygame.sprite import Sprite # v.4
#import os # v.3 (my changes)
from os import path

class Ship(Sprite): # v.4
    """A class to manage the ship."""

    def __init__(self, ai_game):
        """Initialize the ship and set its starting position."""
        super().__init__() # v.4
        self.screen = ai_game.screen
        self.screen_rect = ai_game.screen.get_rect()
        self.settings = ai_game.settings # v.3

        # Load the ship image and get its rect.
        self.dir_path = path.dirname(path.abspath(__file__)) # v.3 (my changes)
        image_path = path.join(self.dir_path, 'images\ship.bmp') # v.3 (my changes)
        #print (f"Image path name: {image_path}") # v.3 (my changes)
        self.image = pygame.image.load(image_path) # v.3 (my changes)
        self.rect = self.image.get_rect()

        # Start each new ship at the bottom center of the screen.
        self.rect.midbottom = self.screen_rect.midbottom

        # Store a decimal value for the ship's horizontal position.
        self.x = float(self.rect.x) # v.3

        # Movement flag
        self.moving_right = False # v.2
        self.moving_left = False # v.3

    def update(self): # v.2
        """Update the ship's position based on the movement flag."""
        if self.moving_right and self.rect.right < self.screen_rect.right: # v.3
            self.x += self.settings.ship_speed # v.3
        if self.moving_left and self.rect.left > 0: # v.3
            self.x -= self.settings.ship_speed # v.3

        # Update rect object from self.x
        self.rect.x = self.x

    def blitme(self):
        """Draw the ship at its current location."""
        self.screen.blit(self.image, self.rect)

    def center_ship(self): # v.3.1
        """Center the ship on the screen."""
        self.rect.midbottom = self.screen_rect.midbottom
        self.x = float(self.rect.x)