#pragma once

#include "editor.h"
#include "resource.h"
#include "player.h"

#include <SDL.h>
#include <SDL_syswm.h>
#include <iostream>

Editor::Editor(std::wstring window_name)
{
    _window = FindWindow(NULL, window_name.c_str());
    if(_window == NULL)
    {
        std::cout << "Failed to find window. Window Name: " << window_name.c_str() << std::endl;
        exit(1);
    }

    _menu = LoadMenu(GetModuleHandle(0), MAKEINTRESOURCE(IDR_MENU1));
    if(_menu == NULL)
    {
        std::cout << "Failed to create menu." << std::endl;
        exit(1);
    }

    BOOL set_menu_result = SetMenu(_window, _menu);
    if(set_menu_result == 0)
    {
        std::cout << "Failed to set menu." << std::endl;
        exit(1);
    }

    Uint8 event_state_result  = SDL_EventState(SDL_SYSWMEVENT, SDL_ENABLE);
    Uint8 event_state_success = SDL_DISABLE;
    if(event_state_result != event_state_success)
    {
        std::cout << "Failed to enable Windows event state." << std::endl;
        exit(1);
    }    
}

Editor::~Editor()
{
}

INT_PTR CALLBACK Dialog_Proc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM)
{
    switch(Message)
    {
    case WM_INITDIALOG:
        return TRUE;
    case WM_COMMAND:
        switch(LOWORD(wParam))
        {
        case IDC_BUTTON1:
            EndDialog(hwnd, IDOK);
            break;
        case IDC_BUTTON_CLOSE:
            EndDialog(hwnd, IDOK);
            break;
        case IDC_VERSION_BTN_CLOSE:
            EndDialog(hwnd, IDOK);
            break;
        }
        break;
    default:
        return FALSE;
    }
    return TRUE;
}


void Editor::update(Input* input, Scene* scene, Configuration* config)
{
    if(input->is_button_state(Input::Button::DECREASE_SPEED, Input::Button_State::PRESSED))
    {
        Player* player = (Player*)scene->get_game_object("Player");
        player->set_speed(player->speed() * 0.9f);
    }

    if(input->is_button_state(Input::Button::INCREASE_SPEED, Input::Button_State::PRESSED))
    {
        Player* player = (Player*)scene->get_game_object("Player");
        player->set_speed(player->speed() * 1.1f);
    }

    if (input->is_button_state(Input::Button::CHANGE_TO_DINO, Input::Button_State::PRESSED))
    {
        Player* player = (Player*)scene->get_game_object("Player");
        player->set_texture("Texture.Dino.Walking");
    }

    if(input->is_button_state(Input::Button::SHOW_CREDITS, Input::Button_State::PRESSED))
    {
        DialogBox(GetModuleHandle(0), MAKEINTRESOURCE(IDD_DIALOG1), _window, Dialog_Proc);
    }

    if (input->is_button_state(Input::Button::SHOW_LIBRARIES, Input::Button_State::PRESSED))
    {
        DialogBox(GetModuleHandle(0), MAKEINTRESOURCE(IDD_DIALOG2), _window, Dialog_Proc);
    }

    if (input->is_button_state(Input::Button::SHOW_VERSION, Input::Button_State::PRESSED))
    {
        DialogBox(GetModuleHandle(0), MAKEINTRESOURCE(IDD_DIALOG3), _window, Dialog_Proc);
    }

    if(input->is_button_state(Input::Button::DEBUG_SHOW_IDS, Input::Button_State::PRESSED))
    {
        config->should_display_ids = !config->should_display_ids;
    }

    if (input->is_button_state(Input::Button::DEBUG_SHOW_POSITION, Input::Button_State::PRESSED))
    {
        config->should_display_position = !config->should_display_position;
    }

    if (input->is_button_state(Input::Button::FULL_SCREEN, Input::Button_State::PRESSED))
    {
        config->window_width = GetSystemMetrics(SM_CXSCREEN);
        config->window_height = GetSystemMetrics(SM_CYSCREEN);

       SetWindowPos(_window, 0, 0, 0, config->window_width, config->window_height, 0L);
    }

    if (input->is_button_state(Input::Button::REVERSE_FULL_SCREEN, Input::Button_State::PRESSED))
    {
        config->window_width = 600;
        config->window_height = 600;

        SetWindowPos(_window, 0, 0, 0, config->window_width, config->window_height, 0L);

    }
}



