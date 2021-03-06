/*!
    @file Engine.cpp
    @brief Класс игрового движка
    @author Власов Александр, Татьяна Мамонтова, Алена Бескровная
    @date Май 2017
*/

#include "Engine.h"

namespace thirtythree{
Engine::Engine(Drawer *drawer, GameLogic *logic, QuadTree *tree)
    : tree_ (tree),
      drawer_ (drawer),
      logic_ (logic) {
    LOG_INFO("Engine created");
}

void Engine::AddObject(GameObject *object) {
    if (GetObjectsCount() < kMaxObjectsCount) {
        object->SetId(id_counter_++);
        objects_.emplace_back(object);
    } else {
        if (object != nullptr) delete object;
        LOG_INFO("Objects limit exceeded!");
    }
}

void Engine::StartGame() {
    logic_->StartGame();
    LOG_INFO("Game initialized");
    GameLoop();
}

void Engine::GameLoop() {
    LOG_INFO("Game loop started");
    while (drawer_->WindowIsOpen()) {
        time_ = clock_.restart().asSeconds();
        HandleEvents();

        if (!game_paused_) {
            logic_->DoLogic();

            drawer_->ClearMap();
            tree_->Prune();
            for (auto& obj : objects_) {
                if (!(obj->IsDead())) {
                    HandleObject(*obj);
                    HandleBorderCollisions(*obj);
                    if (tree_->Insert(obj.get()) == false) {
                            LOG_ERROR("QuadTree building failure, object id = " << obj->GetId());
                    }
                }
            }

            if (draw_quadtree_ == 1) drawer_->VisualizeQuadTree(*tree_);

            for (auto& obj : objects_) {
                if (!(obj->IsDead()) && obj->IsInteractable()) {
                    float obj_radius = obj->GetRadius();
                    float interaction_distance = kObjectInteractionDistance + obj_radius;
                    GameObject *nearest_obj = tree_->FindNearestNeighbor(obj.get(), interaction_distance, draw_quadtree_ == 2);
                    if (nearest_obj != nullptr) {
                        if (Collision(*obj, *nearest_obj)) {
                            GameLogic::Event event(GameLogic::EventType::COLLISION, *obj, *nearest_obj);
                            logic_->HandleEvent(event);
                        } else {
                            GameLogic::Event event(GameLogic::EventType::INTERACTION, *obj, *nearest_obj);
                            logic_->HandleEvent(event);
                        }


                    }
                }
            }
            HandleDeadObjects();
        }

        drawer_->DisplayMap();
        drawer_->ClearWindow();
        drawer_->DrawMap();
        DrawUI();
        drawer_->DisplayWindow();

    }
}

void Engine::RestartGame() {
    game_over_ = false;
    //objects_.clear();
    StartGame();
}

void Engine::HandleEvents() {
    sf::Event event;
    while (drawer_->PollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed: {
                drawer_->CloseWindow();
                break;
            }
            case sf::Event::Resized: {
                drawer_->ResizeWindow(event.size.width, event.size.height);
                break;
            }
            case sf::Event::KeyPressed: {
                switch (event.key.code) {
                    case sf::Keyboard::Tab: {
                        draw_debug_info_ = !draw_debug_info_;
                        break;
                    }
                    case sf::Keyboard::R: {
                        if (game_over_) RestartGame();
                        break;
                    }
                    case sf::Keyboard::Escape: {
                        game_paused_ = !game_paused_;
                        break;
                    }
                    case sf::Keyboard::Q: {
                        draw_quadtree_ = (draw_quadtree_ + 1) % 3;
                        break;
                    }
                    case sf::Keyboard::W: {
                        draw_obj_id_ = (draw_obj_id_ + 1) % 3;
                        break;
                    }
                    default: {}
                }
                break;
            }
            case sf::Event::MouseWheelMoved: {
                drawer_->ZoomWindow(event.mouseWheel.delta);
                break;
            }
            default: {}
        }
    }
}

void Engine::HandleObject(GameObject &obj) {
    if (obj.GetType() == PLAYER) {
        drawer_->SetViewCenter(obj.GetPos());
        obj.Control();
    }
    obj.Logic();
    obj.Move(time_);
    drawer_->DrawObject(obj);
    if (draw_debug_info_ && draw_obj_id_) {
        if (draw_obj_id_ == 2 || obj.IsInteractable()) {
            std::string info = std::to_string(obj.GetId());
            Drawer::Text obj_info(info, 40, obj.GetPos(), sf::Color::Blue, true, true);
            drawer_->DrawText(obj_info);
        }
    }
}

void Engine::HandleBorderCollisions(GameObject &obj) {

    auto pos = obj.GetPos();
    auto radius = obj.GetRadius();
    auto speed = obj.GetSpeed();
    auto map_size = GetMapSize();

    if (pos.x < radius) {
        speed.x = abs(speed.x);
        pos.x = radius;
    } else if (pos.x > map_size.x - radius) {
        speed.x = -abs(speed.x);
        pos.x = map_size.x - radius;
    }
    if (pos.y < radius) {
        speed.y = abs(speed.y);
        pos.y = radius;
    } else if (pos.y > map_size.y - radius) {
        speed.y = -abs(speed.y);
        pos.y = map_size.y - radius;
    }
    obj.SetPos(pos);
    obj.SetSpeed(speed);

//    if (pos.x < 0) {
//        pos.x += map_size.x;
//    } else if (pos.x > map_size.x) {
//        pos.x -= map_size.x;
//    }
//    if (pos.y < 0) {
//        pos.y += map_size.y;
//    } else if (pos.y > map_size.y) {
//        pos.y -= map_size.y;
//    }
//    obj.SetPos(pos);
}

void Engine::HandleDeadObjects() {

    auto obj = std::begin(objects_);
    while (obj != std::end(objects_)) {
        if ((*obj)->IsDead()) {
            if ((*obj)->GetType() == PLAYER) game_over_ = true;
            obj = objects_.erase(obj);
        } else {
            obj++;
        }
    }

}

void Engine::DrawUI() {

    if (game_over_) {
        sf::Vector2f pos1 = GetWindowSize() / 2.0f;
        sf::Vector2f pos2 = pos1 + sf::Vector2f(0, 45);
        sf::Vector2f pos3 = pos2 + sf::Vector2f(0, 24);
        drawer_->DrawText(Drawer::Text("Game over!", 45, pos1, true));
        drawer_->DrawText(Drawer::Text("Your score is " + std::to_string(logic_->GetScore()), 24, pos2, true));
        drawer_->DrawText(Drawer::Text("Press R to restart", 24, pos3, true));
    } else {
        drawer_->DrawText(Drawer::Text("Score: " + std::to_string(logic_->GetScore()), 25, {5, 0}));
    }
    if (draw_debug_info_) {
        DrawDebugInfo();
    }

}

void Engine::DrawDebugInfo() {
    int fps = 1.f / time_;
    std::string debug_text = "FPS: " + std::to_string(fps) + "\nObj. count: " +
                             std::to_string(GetObjectsCount());
    sf::Vector2f pos = {0, GetWindowSize().y - 45};
    drawer_->DrawText(Drawer::Text(debug_text, 20, pos));
}

}
