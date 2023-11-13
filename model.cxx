#include "model.hxx"
//definition: "ghost tap" = pressing key and hitting nothing, i.e. no objects
// on screen or objects too far outside of hit windows
Model::Model():
    recep1(receptor1),
    recep2(receptor2),
    recep3(receptor3),
    recep4(receptor4)
{
    score = 0;
    combo = 0;
    time_passed = 0;
}

void
Model::delete_obj(object obj) //deletes given object
{
    int idx = 0;
    for (object obj2: objects) {
        if (obj.pos == obj2.pos) {
            break;
        }
        idx += 1;
    }
    objects.erase(objects.begin() + idx);
}
void
Model::calc_points(object receptor, object obj)
{
    if ((obj.center.y < receptor.center.y + perfect) && (obj.center.y >
                                                       receptor.center.y
                                                       - perfect)) {
        score_array.push_back(300); //updates accuracy weight array
        combo += 1; //increments combo
        delete_obj(obj); //deletes hit object
        object_hit = true; //communicate with view object was hit
        hit_obj_val = 300; //communicate with view the accuracy score of hit
        return;
    }
    else if ((obj.center.y < receptor.center.y + great) && (obj.center.y >
                                                           receptor.center.y
                                                           - great)) {
        score_array.push_back(200);
        combo += 1;
        delete_obj(obj);
        object_hit = true;
        hit_obj_val = 200;
        return;
    }
    else if ((obj.center.y < receptor.center.y + okay) && (obj.center.y >
                                                            receptor.center.y
                                                            - okay)) {
        score_array.push_back(100);
        combo += 1;
        delete_obj(obj);
        object_hit = true;
        hit_obj_val = 100;
        return;
    }
    else if ((obj.center.y < receptor.center.y + miss) && (obj.center.y >
                                                            receptor.center.y
                                                            - miss)) {
        score_array.push_back(0);
        combo = 0;
        delete_obj(obj);
        object_hit = true;
        hit_obj_val = 0;
        return;
    }
    else {
        hit_obj_val = 2; //denoting ghost tap, no points added.
        object_hit = false;
        return;
    }
}

float
Model::calc_accuracy() //updates the current accuracy by taking a weighted
// average of the scores
{
    int sum = 0;
   for (int i: score_array) {
        sum += i;
   }
   return sum/score_array.size();
}

bool
Model::fall_below_screen(Model::object obj)
{
    if (obj.pos.y > screen_height) {
        score_array.push_back(0); //add a weight of 0 into accuracy calculation
        time_since_hit = 0; //reset this to tell the view to print sprite
        hit_obj_val = 0;//communicates with view that an object was missed
        object_hit = true; //technically not true, but set to true for
        // purposes of telling view to print a "miss" sprite
        return true;
    }
    else {
        return false;
    }
}

void
Model::generate_objects(object receptor) //used for generating custom maps
{
    object new_obj({receptor.pos.x, 0});
    objects.push_back(new_obj);
}

void
Model::on_hit(Model::object receptor) //when key is pressed, this function is
// called
{
    int lowest_y = 0; //find the lowest y position of all the objects
    for (object obj: objects) {
        if (obj.pos.x == receptor.pos.x) {
            if (obj.pos.y > lowest_y) {
                lowest_y = obj.pos.y;
            }
        }
    }
    object hit_obj({0,0}); //grab the lowest object
    for (object obj: objects) {
        if (obj.pos.y == lowest_y) {
            hit_obj.pos = {obj.pos.x, obj.pos.y};
        }
    }
    //perform hit/accuracy computations
    calc_points(receptor, hit_obj);
    accuracy = calc_accuracy();
    time_since_hit = 0; //reset every time an object is hit
}

int
Model::calc_total_score() //calculate total score accumulated
{
    int sum = 0;
    for (int score: score_array) {
        sum += score;
    }
    return sum;
}

void
Model::on_frame(double dt)
{
    for (object obj: objects) { //move all objects down every frame, delete
        // ones that fall below the screen
        obj.pos.y + (dt*obj_speed);
        if (fall_below_screen(obj)) {
            delete_obj(obj);
        }
    }
    score = calc_total_score();
    frame += 1;
    time_passed += dt;
    if (hit_obj_val != 2) { //if player didn't ghost tap, increment
        // time_since_hit
        time_since_hit += dt;
    }
}

bool
Model::game_over()
{
    if (time_passed > song_length) { //if we pass more time than length of
        // song, game is over.
        return true;
    }
    else {
        return false;
    }
}
