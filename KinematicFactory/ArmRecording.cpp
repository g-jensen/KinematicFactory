//#include "ArmRecording.h"
//
//ArmRecording::ArmRecording(Arm* arm)
//{
//    this->arm = arm;
//    animation = PositionAnimation(&temp, AnimationType::LINEAR, { 0,0 }, 100);
//    playing_recording = false;
//    recording_iteration = 0;
//    temp = sf::Transformable();
//}
//
//void ArmRecording::add_recording_point(sf::Vector2f point)
//{
//    recorded_points.push_back(point);
//}
//
//void ArmRecording::set_recording_points(std::vector<sf::Vector2f> points)
//{
//    this->recorded_points = points;
//}
//
//void ArmRecording::update_recording()
//{
//    if (playing_recording) {
//        animation.iterate();
//        arm->follow((sf::Vector2<double>)temp.getPosition());
//        if (animation.isFinished()) {
//            if (recording_iteration + 1 < recorded_points.size()) {
//                recording_iteration++;
//                double len = _Math::length((sf::Vector2<double>)recorded_points[recording_iteration - 1], (sf::Vector2<double>)recorded_points[recording_iteration]);
//                animation = PositionAnimation(&temp, AnimationType::LINEAR, { recorded_points[recording_iteration] }, (int)(len / 4));
//            }
//            else {
//                playing_recording = false;
//                recording_iteration = 0;
//            }
//        }
//    }
//}
//
//void ArmRecording::stop_recording()
//{
//    playing_recording = false;
//    recording_iteration = 0;
//}
//
//void ArmRecording::reset_recording()
//{
//    recorded_points.clear();
//    recording_iteration = 0;
//}
//
//void ArmRecording::play_recording()
//{
//    playing_recording = true;
//    temp.setPosition((sf::Vector2f)arm->get_end());
//    double len = _Math::length(arm->get_end(), (sf::Vector2<double>)recorded_points[recording_iteration]);
//    animation = PositionAnimation(&temp, AnimationType::LINEAR, { recorded_points[recording_iteration] }, (int)(len / 4));
//}
