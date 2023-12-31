class Settings:
    """A class to store all settings for Alien Invasion."""

    def __init__(self):
        """Initialize the game's static settings."""
        # Screen settings
        self.screen_width = 1200
        self.screen_height = 800
        self.bg_color = (230, 230, 230)

        # Ship settings
        self.ship_speed = 1.5 # v.2
        self.ship_limit = 3 # v.5.1

        # Bullet settings
        self.bullet_speed = 2.5 # v.3
        self.bullet_width = 3 # v.3
        self.bullet_height = 15 # v.3
        self.bullet_color = (60, 60, 60) # v.3
        self.bullets_allowed = 5 # v.4

        # Alien settings
        self.alien_speed = 1.0 # v.5
        self.fleet_drop_speed = 10 # v.5
        # fleet_direction of 1 represents right; -1 represents left.
        self.fleet_direction = 1 # v.5