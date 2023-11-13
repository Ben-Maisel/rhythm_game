#include "controller.hxx"

Controller::Controller()
        : model_(),
        view_(model_)
{ }

void
Controller::draw(ge211::Sprite_set& set)
{
    view_.draw(set);
}

void
Controller::on_key(ge211::Key key)
{
    if (key == ge211::Key::code('q')) {
        quit();
    }
    if (key == ge211::Key::code('z')) {
        model_.on_hit(model_.recep1);
    }
    if (key == ge211::Key::code('x')) {
        model_.on_hit(model_.recep2);
    }
    if (key == ge211::Key::code(',')) {
        model_.on_hit(model_.recep3);
    }
    if (key == ge211::Key::code('.')) {
        model_.on_hit(model_.recep4);
    }
}

Dimensions
Controller::initial_window_dimensions() const
{
    return view_.screen_dims();
}

std::string
Controller::initial_window_title() const
{
    return view_.window_title();
}