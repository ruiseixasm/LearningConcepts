import sys
from time import sleep # v.20
import pygame
from settings_6 import Settings # v.21
from game_stats_2 import GameStats # v.21
from scoreboard_3 import Scoreboard # v.24
from button import Button # v.21
from ship_4 import Ship # v.24
from bullet import Bullet # v.11
from alien_2 import Alien # v.18

class AlienInvasion:
    """Overall class to manage game assets and behavior."""

    def __init__(self):
        """Initialize the game, and create game resources."""
        pygame.init() # Calls pygame.joystick.init() automatically
        print (f"Number of connected joysticks: {pygame.joystick.get_count()}") # v.21
        self.settings = Settings()

        # display=0 (Asus) | display=1 (Lenovo)
        self.screen = pygame.display.set_mode((0, 0), pygame.FULLSCREEN, display=0) # v.10
        self.settings.screen_width = self.screen.get_rect().width # v.9
        self.settings.screen_height = self.screen.get_rect().height # v.9
        pygame.display.set_caption("Alien Invasion")

        # Create an instance to store game statistics.
        self.stats = GameStats(self) # v.20
        # Create a scoreboard.
        self.sb = Scoreboard(self) # v.22

        self.ship = Ship(self)
        self.bullets = pygame.sprite.Group() # v.11
        self.aliens = pygame.sprite.Group() # v.14

        self._create_fleet() # v.14

        # Make the Play button.
        self.play_button = Button(self, "Play") # v.21

    def run_game(self):
        """Start the main loop for the game."""
        while True:
            # Refactoring into a method
            self._check_events() # v.4
            if self.stats.game_active: # v.20
                self.ship.update() # v.6
                self._update_bullets() # v.13
                self._update_aliens() # v.18
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
            elif event.type == pygame.MOUSEBUTTONDOWN: # v.21
                mouse_pos = pygame.mouse.get_pos()
                self._check_play_button(mouse_pos)

    def _check_play_button(self, mouse_pos): # v.21
        """Start a new game when the player clicks Play."""
        button_clicked = self.play_button.rect.collidepoint(mouse_pos)
        if button_clicked and not self.stats.game_active:
            # Reset the game statistics.
            self.settings.initialize_dynamic_settings()
            self.stats.reset_stats()
            self.stats.game_active = True
            self.sb.prep_score() # v.22
            self.sb.prep_level() # v.23
            self.sb.prep_ships() # v.24

            # Hide the mouse
            pygame.mouse.set_visible(False)

            # Get rid of any remaining aliens and bullets.
            self.aliens.empty()
            self.bullets.empty()

            # Create a new fleet and center the ship.
            self._create_fleet()
            self.ship.center_ship()

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

    def _create_fleet(self): # v.14, v.15
        """Create the fleet of aliens."""
        # Create an alien and find the number of aliens in a row.
        # Spacing between each alien is equal to one alien width.
        alien = Alien(self) # v.14
        alien_width, alien_height = alien.rect.size # v.17
        available_space_x = self.settings.screen_width - alien_width
        number_aliens_x = available_space_x // (2 * alien_width)

        # Determine the number of rows of aliens that fit on the screen.
        ship_height = self.ship.rect.height # v.17
        available_space_y = self.settings.screen_height - 3 * alien_height - 2 * ship_height # v.17
        number_rows = available_space_y // (2 * alien_height) # v.17

        # Create the full fleet of aliens.
        for row_number in range(number_rows): # v.17
            for alien_number in range(number_aliens_x): # v.15
                self._create_alien(alien_number, row_number) # v.17

    def _create_alien(self, alien_number, row_number): # v.17
        """Create an alien and place it in the row."""
        alien = Alien(self)
        alien_width, alien_height = alien.rect.size # v.17
        alien.x = alien_width + 2 * alien_width * alien_number
        alien.rect.x = alien.x
        alien.rect.y = alien.rect.height + 2 * alien.rect.height * row_number # v.17
        self.aliens.add(alien) # v.14

    def _fire_bullet(self): # v.11
        """Create a new bullet and add it to the bullets group."""
        if len(self.bullets) < self.settings.bullets_allowed: # v.12
            new_bullet = Bullet(self)
            self.bullets.add(new_bullet)

    def _update_bullets(self): # v.13
        """Update position of bullets and get rid of old bullets."""
        # Update bullet positions.
        self.bullets.update() # v.11
        
        # Get rid of bullets that have disappeared.
        for bullet in self.bullets.sprites(): # v.12 (no need for .copy()) <----- CORRECTION (.sprites())
            if bullet.rect.bottom <= 0:
                self.bullets.remove(bullet)
        # print(len(self.bullets)) # v.12
        self._check_bullet_alien_acollisions() # v.20

    def _check_bullet_alien_acollisions(self): # v.20
        # Check for any bullets that have hit aliens.
        #   If so, get rid of the bullet and the alien.
        collisions = pygame.sprite.groupcollide(self.bullets, self.aliens, True, True) # v.19
        
        if collisions: # v.22
            for aliens in collisions.values():
                self.stats.score += self.settings.alien_points * len(aliens)
            self.sb.prep_score()
            self.sb.check_high_score() # v.23

        if not self.aliens: # v.19
            # Destroy existing bullets and create new fleet.
            self.bullets.empty()
            self._create_fleet()
            self.settings.increase_speed() # v.21

            # Increase level.
            self.stats.level += 1 # v.23
            self.sb.prep_level() # v.23

    def _ship_hit(self): # v.20
        """Respond to the ship being hit by an alien."""
        if self.stats.ships_left > 0:
            # Decrement ships left.
            self.stats.ships_left -= 1
            self.sb.prep_ships() # v.24

            # Get rid of any remaining aliens and bullets.
            self.aliens.empty()
            self.bullets.empty()

            # Create a new fleet and center the ship.
            self._create_fleet()
            self.ship.center_ship()
            # Pause.
            sleep(0.5)
        else:
            self.stats.game_active = False
            pygame.mouse.set_visible(True)

    def _check_aliens_bottom(self): # v.20
        """Check if any aliens have reached the bottom of the screen."""
        screen_rect = self.screen.get_rect()
        for alien in self.aliens.sprites():
            if alien.rect.bottom >= screen_rect.bottom:
                # Treat this the same as if the ship got hit.
                self._ship_hit()
                break

    def _update_aliens(self): # v.18
        """Check if the fleet is at an edge."""
        self._check_fleet_edges()
        """Update the positions of all aliens in the fleet."""
        self.aliens.update()

        # Look for alien-ship collisions.
        if pygame.sprite.spritecollideany(self.ship, self.aliens): # v.20
            self._ship_hit()

        # Look for aliens hitting the bottom of the screen.
        self._check_aliens_bottom() # v.20

    def _check_fleet_edges(self): # v.18
        """Respond appropriately if any aliens have reached an edge."""
        for alien in self.aliens.sprites():
            if alien.check_edges():
                self._change_fleet_direction()
                break

    def _change_fleet_direction(self): # v.18
        """Drop the entire fleet and change the fleet's direction."""
        for alien in self.aliens.sprites():
            alien.rect.y += self.settings.fleet_drop_speed
        self.settings.fleet_direction *= -1

    def _update_screen(self): # v.4
        # Redraw the screen during each pass through the loop.
        self.screen.fill(self.settings.bg_color)
        self.ship.blitme()
        for bullet in self.bullets.sprites(): # v.11
            bullet.draw_bullet()
        self.aliens.draw(self.screen) # v.14

        # Draw the score information.
        self.sb.show_score() # v.22

        # Draw the play button if the game is inactive.
        if not self.stats.game_active: # v.21
            self.play_button.draw_button()

        # Make the most recently draw screen visible.
        pygame.display.flip()


if __name__ == '__main__':
    # Make a game instance, and run the game.
    ai = AlienInvasion()
    ai.run_game()