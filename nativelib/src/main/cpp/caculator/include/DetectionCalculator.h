//
// Created by newst on 2022-09-25.
//

#ifndef BODA_DETECTIONCALCULATOR_H
#define BODA_DETECTIONCALCULATOR_H

#include <vector>

struct Anchor {
    float x;  // [0.0-1.0]
    float y;  // [0.0-1.0]
    float z;  // Centered around 1.0 [current_scale = z * initial_scale]
    int sticker_id;
};

class DetectionCalculator {
public:
    DetectionCalculator() = default;

    void process(const float* output);
private:
    void generateAnchors(std::vector<Anchor>& anchors);

    // SsdAnchorsCalculatorOptions
    unsigned int num_layers {4};
    float min_scale {0.1484375};
    float max_scale {0.75};
    unsigned int input_size_height {128};
    unsigned int input_size_width {128};
    float anchor_offset_x {0.5};
    float anchor_offset_y {0.5};
    std::vector<unsigned int> strides{8, 16, 16, 16};
    float aspect_ratios {1.0};
    bool fixed_anchor_size {true};

    // TfLiteTensorsToDetectionsCalculatorOptions
    unsigned int num_classes {1};
    unsigned int num_boxes {896};
    unsigned int num_coords {16};
    unsigned int box_coord_offset {0};
    unsigned int keypoint_coord_offset {4};
    unsigned int num_keypoints {6};
    unsigned int num_values_per_keypoint {2};
    bool sigmoid_score {true};
    float score_clipping_thresh {100.0};
    bool reverse_output_order {true};
    float x_scale {128.0};
    float y_scale {128.0};
    float h_scale {128.0};
    float w_scal {128.0};
    float min_score_thresh {0.75};
};


#endif //BODA_DETECTIONCALCULATOR_H
