//
// Created by nicola on 10/11/17.
//

#ifndef FUSION_RECTANGLE_H
#define FUSION_RECTANGLE_H


#include <vector>
#include <ostream>
#include "Point2D.h"
#include "Shape.h"

namespace Geometry {
    /**
     * @class Rectangle
     * Rectangle parallel to the plane axis
     */
    class Rectangle : public Shape {
        long xmin, xmax, ymin, ymax;

    public:
        Rectangle() { xmin = xmax = ymin = ymax = 0; }

        /**
         * Constructor.
         * @param xmin
         * @param xmax
         * @param ymin
         * @param ymax
         */
        Rectangle(long xmin, long xmax, long ymin, long ymax) : xmin(xmin), xmax(xmax), ymin(ymin), ymax(ymax) {}

        /**
         * Constructor.
         * @param vertices Array of vertices.
         */
        explicit Rectangle(std::vector<Point2D> &vertices);

        /**
         * Constructor.
         * @param p1 top-left corner
         * @param p2 bottom-right corner
         */
        Rectangle(Point2D p1, Point2D p2);

        /**
         * Constructor.
         * @param p_up_left to-left corner
         * @param width
         * @param height
         */
        Rectangle(Point2D p_up_left, long width, long height);

        ~Rectangle() override = default;

        double computeArea() const override;

        bool has_inside(Point2D p) const override;

        /**
         * Intersect a Rectangle with another one.
         * @param The other Rectangle.
         * @return The resulting intersection Rectangle.
         */
        Rectangle intersect(const Rectangle &other) const;

        /**
         * Apply difference operator with another Rectangle.
         * @param other The other Rectangle
         * @return Array of Rectangles of size from 0 to 4.
         */
        std::vector<Rectangle> difference(const Rectangle &other) const;

        /**
         * Get xmin.
         * @return xmin
         */
        long getXmin() const;

        /**
         * Get xmax.
         * @return xmax
         */
        long getXmax() const;

        /**
         * Get ymin.
         * @return ymin
         */
        long getYmin() const;

        /**
         * Get ymax.
         * @return ymax
         */
        long getYmax() const;

        /**
         * Set xmin.
         * @param xmin
         */
        void setXmin(long xmin);

        /**
         * Set xmax.
         * @param xmax
         */
        void setXmax(long xmax);

        /**
         * Set ymin.
         * @param ymin
         */
        void setYmin(long ymin);

        /**
         * Set ymax.
         * @param ymax
         */
        void setYmax(long ymax);

        friend std::ostream &operator<<(std::ostream &os, const Rectangle &rectangle);


    private:
        bool equal_to(Shape const &rhs) const override;


    };

}


#endif //FUSION_RECTANGLE_H
