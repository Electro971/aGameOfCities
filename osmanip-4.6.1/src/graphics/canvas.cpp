//====================================================
//     File data
//====================================================
/**
 * @file canvas.cpp
 * @author Miguel MJ (miguelmjvg@gmail.com)
 * @date 2022-06-06
 * @copyright Copyright (c) 2022 Gianluca Bianco
 * under the MIT license.
 */

//====================================================
//     Headers
//====================================================

// My headers
#include <osmanip/graphics/canvas.hpp>
#include <osmanip/manipulators/colsty.hpp>
#include <osmanip/manipulators/common.hpp>
#include <osmanip/manipulators/cursor.hpp>
#include <osmanip/utility/iostream.hpp>

// STD headers
#include <cstdint>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

namespace osm {

    //====================================================
    //     Variables
    //====================================================
    const std::vector<std::vector<std::string>> Canvas::frames{
        //   TL,  T,   TR,  L,   R,   BL,  B,   BR
        {" ", " ", " ", " ", " ", " ", " ", " "},
        {"+", "-", "+", "|", "|", "+", "-", "+"},
        {"\u250c", "\u2500", "\u2510", "\u2502", "\u2502", "\u2514", "\u2500", "\u2518"}};

    //====================================================
    //     Constructors
    //====================================================

    // Parametric constructor
    /**
     * @brief Construct a new Canvas:: Canvas
     * object. The size of the canvas in
     * characters must be specified upon
     * construction.
     *
     * @param width Width of the canvas.
     * @param height Height of the canvas.
     */
    Canvas::Canvas(uint32_t width, uint32_t height)
        : already_drawn_(false), width_(width), height_(height), bg_char_(' '), bg_feat_(""), frame_enabled_(false) {
        resizeCanvas();
        clear();
    }

    //====================================================
    //     Setters
    //====================================================

    // setBackground
    /**
     * @brief Set the char that fills the
     * background and an optional feat.
     *
     * @param c The char that fills the
     * background.
     * @param feat The optional feat.
     */
    void Canvas::setBackground(char c, std::string_view feat) {
        bg_char_ = c;
        bg_feat_ = feat;
    }

    // setFrame
    /**
     * @brief Set the FrameStyle of the canvas and
     * an optional feat.
     *
     * @param fs The FrameStyle of the canvas.
     * @param feat The optional feature.
     */
    void Canvas::setFrame(FrameStyle fs, std::string_view feat) {
        frame_style_ = fs;
        frame_feat_ = feat;
    }

    // setWidth
    /**
     * @brief Set the width of the canvas.
     *
     * @param width The canvas width to set.
     */
    void Canvas::setWidth(uint32_t width) {
        width_ = width;
        resizeCanvas();
    }

    // setHeight
    /**
     * @brief Set the height of the canvas.
     *
     * @param height The canvas height to set.
     */
    void Canvas::setHeight(uint32_t height) {
        height_ = height;
        resizeCanvas();
    }

    //====================================================
    //     Getters
    //====================================================

    // getWidth
    /**
     * @brief Get the width of the canvas.
     *
     * @return uint32_t The width of the canvas.
     */
    uint32_t Canvas::getWidth() const { return width_; }

    // getHeight
    /**
     * @brief Get the height of the canvas.
     *
     * @return uint32_t The height of the canvas.
     */
    uint32_t Canvas::getHeight() const { return height_; }

    // getBackground
    /**
     * @brief Get the char that fills the
     * background.
     *
     * @return char The char that fills the
     * background.
     */
    char Canvas::getBackground() const { return bg_char_; }

    // getBackgroundFeat
    /**
     * @brief Get the optional feat of the
     * background.
     *
     * @return std::string The optional feat of
     * the background.
     */
    std::string Canvas::getBackgroundFeat() const { return bg_feat_; }

    // getFrameFeat
    /**
     * @brief Get the frame feature (if set).
     *
     * @return std::string The frame feature.
     */
    std::string Canvas::getFrameFeat() const { return frame_feat_; }

    // getFrameStyle
    /**
     * @brief Get the frame style.
     *
     * @return FrameStyle The frame style.
     */
    FrameStyle Canvas::getFrameStyle() const { return frame_style_; }

    //====================================================
    //     Methods
    //====================================================

    // enableFrame
    /**
     * @brief Flag to frame or not the canvas. The
     * frame doesn't increase the size taken by
     * the canvas. Instead, reduces the 2D space
     * to draw in two columns and two rows (used
     * to print the frame itself).
     *
     * @param frame_enabled Set to True to enable
     * the frame. Otherwise set to False.
     */
    void Canvas::enableFrame(bool frame_enabled) { frame_enabled_ = frame_enabled; }

    // isFrameEnabled
    /**
     * @brief Return True if the frame is enabled.
     * Otherwise return False.
     *
     * @return bool The frame enabled flag.
     */
    bool Canvas::isFrameEnabled() const { return frame_enabled_; }

    // clear
    /**
     * @brief Fill the canvas with the background.
     */
    void Canvas::clear() {
        char_buffer_.assign(static_cast<int64_t>(width_) * height_, bg_char_);
        feat_buffer_.assign(static_cast<int64_t>(width_) * height_, bg_feat_);
    }

    // put
    /**
     * @brief Put a character in the canvas, given
     * its coordinates and an optional feat. An
     * out-of-bounds exception will be thrown if
     * the coordinates are outside the canvas.
     *
     * @param c The char to put.
     * @param x The x position.
     * @param y The y position.
     * @param feat The optional feature.
     */
    void Canvas::put(uint32_t x, uint32_t y, char c, std::string_view feat) {
        char_buffer_.at(y * width_ + x) = c;
        feat_buffer_.at(y * width_ + x) = feat;
    }

    // refresh
    /**
     * @brief Display the canvas in the console.
     */
    void Canvas::refresh() {
        if (already_drawn_) {
            for (uint32_t i{0}; i < height_; i++) {
                osm::cout << feat(crs, "up", 1);
            }
        }

        uint32_t y{0};

        const auto &frame = [&](uint32_t fi) -> std::string {
            return frame_feat_ + frames[frame_style_][fi] + feat(rst, "all");
        };

        std::stringstream ss;

        if (frame_enabled_) {
            ss << frame(0);

            for (uint32_t i{2}; i < width_; i++) {
                ss << frame(1);
            }

            ss << frame(2) << std::endl;
            y++;
        }

        for (; y < height_; y++) {
            if (y == height_ - 1 && frame_enabled_) {
                ss << frame(5);

                for (uint32_t i{2}; i < width_; i++) {
                    ss << frame(6);
                }

                ss << frame(7) << std::endl;
                continue;
            }

            for (uint32_t x{0}; x < width_; x++) {
                if (x == 0 && frame_enabled_) {
                    ss << frame(3);
                    continue;
                }

                if (x == width_ - 1 && frame_enabled_) {
                    ss << frame(4);
                    continue;
                }

                uint32_t p = y * width_ + x;

                ss << feat_buffer_[p] << char_buffer_[p] << feat(rst, "all");
            }
            ss << std::endl;
        }
        osm::cout << ss.str();
        already_drawn_ = true;
    }

    // resizeCanvas
    /**
     * @brief Resize the canvas.
     */
    void Canvas::resizeCanvas() {
        char_buffer_.resize(static_cast<int64_t>(width_) * height_);
        feat_buffer_.resize(static_cast<int64_t>(width_) * height_);
    }
}  // namespace osm