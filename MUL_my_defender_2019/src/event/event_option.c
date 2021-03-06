/*
** EPITECH PROJECT, 2020
** MUL_my_defender_2019
** File description:
** event_option
*/

#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include "struct_defender.h"
#include "defender.h"
#include "my.h"

void option_mouse_over(window_t *win, game_t *game)
{
    win->mouse_vect = sfMouse_getPositionRenderWindow(win->window);

    for (int i = 0; i < game->def_scene[1].nb_button; i++) {
        if (sfFloatRect_contains(&(game->def_scene[1].button[i].rect),
            win->mouse_vect.x, win->mouse_vect.y)) {
            sfSprite_setTextureRect(game->def_scene[1].button[i].b_sprite.img,
                game->def_scene[1].button[i].rect_tab[1]);
        } else {
            sfSprite_setTextureRect(game->def_scene[1].button[i].b_sprite.img,
                                    game->def_scene[1].button[i].rect_tab[0]);
        }
    }
}

void option_click_evt(window_t *win, game_t *game, int img)
{
    if (game->def_scene[1].event.type == sfEvtMouseButtonReleased) {
        game->def_scene[1].button[img].fct(NULL, win, game);
        sfSprite_setTextureRect(game->def_scene[1].button[img].b_sprite.img,
                                game->def_scene[1].button[img].rect_tab[1]);
    }
}

void option_evt_mouse(window_t *win, game_t *game)
{
    int i = 0;

    win->mouse_vect = sfMouse_getPositionRenderWindow(win->window);
    for (; i < game->def_scene[1].nb_button; i++) {
        if (sfFloatRect_contains(&(game->def_scene[1].button[i].rect),
            win->mouse_vect.x, win->mouse_vect.y)) {
            sfSprite_setTextureRect(game->def_scene[1].button[i].b_sprite.img,
                                    game->def_scene[1].button[i].rect_tab[2]);
            option_click_evt(win, game, i);
        }
    }
}

void option_evt_poll(window_t *win, game_t *game)
{
    switch (game->def_scene[1].event.type) {
        case sfEvtClosed :
            sfRenderWindow_close(win->window);
            break;
        case sfEvtMouseButtonPressed :
        case sfEvtMouseButtonReleased :
            option_evt_mouse(win, game);
            break;
        default:
            option_mouse_over(win, game);
            break;
    }
}

int manage_event_option(window_t *win, game_t *game)
{
    while (sfRenderWindow_pollEvent(win->window, &game->def_scene[1].event)) {
        option_evt_poll(win, game);
    }
    return (0);
}