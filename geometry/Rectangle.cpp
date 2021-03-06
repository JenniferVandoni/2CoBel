//
// Created by nicola on 10/11/17.
//

#include <cmath>
#include <stdexcept>
#include "../errors/ConstructorArgumentsError.h"
#include <cfloat>
#include "Rectangle.h"


namespace Geometry {


    bool isOrthogonal(const Point2D &a, const Point2D &b, const Point2D &c) {
        return std::fabs((b.X() - a.X()) * (b.X() - c.X()) + (b.Y() - a.Y()) * (b.Y() - c.Y())) < FLT_EPSILON;
    }

    bool isRectangle(std::vector<Point2D> &vertices) {
        return isOrthogonal(vertices[0], vertices[1], vertices[2]) &&
               isOrthogonal(vertices[1], vertices[2], vertices[3]) &&
               isOrthogonal(vertices[2], vertices[3], vertices[0]) &&
               (vertices[0].X() == vertices[1].X() || vertices[0].Y() == vertices[1].Y());
    }

    Rectangle::Rectangle(std::vector<Point2D> &vertices) {
        if (vertices.size() != 4) throw ConstructorArgumentsError("Rectangle: wrong number of vertices");
        if (!isRectangle(vertices)) throw ConstructorArgumentsError("Rectangle: ill-defined rectangle");
        xmin = std::min(std::min(vertices[0].X(), vertices[1].X()), std::min(vertices[2].X(), vertices[3].X()));
        xmax = std::max(std::max(vertices[0].X(), vertices[1].X()), std::max(vertices[2].X(), vertices[3].X()));
        ymin = std::min(std::min(vertices[0].Y(), vertices[1].Y()), std::min(vertices[2].Y(), vertices[3].Y()));
        ymax = std::max(std::max(vertices[0].Y(), vertices[1].Y()), std::max(vertices[2].Y(), vertices[3].Y()));
    }

    Rectangle::Rectangle(Point2D p1, Point2D p2) {
        if (p1.X() == p2.X() || p1.Y() == p2.Y()) throw ConstructorArgumentsError("Rectangle: ill-defined rectangle");
        xmin = std::min(p1.X(), p2.X());
        xmax = std::max(p1.X(), p2.X());
        ymin = std::min(p1.Y(), p2.Y());
        ymax = std::max(p1.Y(), p2.Y());
    }

    Rectangle::Rectangle(Point2D p_up_left, long width, long height) {
        xmin = p_up_left.X();
        xmax = xmin + width;
        ymax = p_up_left.Y();
        ymin = ymax - height;
    }

    double Rectangle::computeArea() const {
        return (xmax - xmin) * (ymax - ymin);
    }


    bool Rectangle::has_inside(const Point2D p) const {
        return p.X() >= xmin && p.X() <= xmax && p.Y() >= ymin && p.Y() <= ymax;
    }

    Rectangle Rectangle::intersect(const Rectangle &other) const {
        long n_xmin = std::max(xmin, other.getXmin());
        long n_xmax = std::min(xmax, other.getXmax());
        long n_ymin = std::max(ymin, other.getYmin());
        long n_ymax = std::min(ymax, other.getYmax());
        if (n_xmin >= n_xmax || n_ymin >= n_ymax) return Rectangle(INT64_MAX, INT64_MAX, INT64_MAX, INT64_MAX);
        return Rectangle(n_xmin, n_xmax, n_ymin, n_ymax);
    }


    long Rectangle::getXmin() const {
        return xmin;
    }

    long Rectangle::getXmax() const {
        return xmax;
    }

    long Rectangle::getYmin() const {
        return ymin;
    }

    long Rectangle::getYmax() const {
        return ymax;
    }

    bool Rectangle::equal_to(Shape const &rhs) const {
        auto rhsr = static_cast<const Rectangle &>(rhs);
        return xmin == rhsr.xmin &&
               xmax == rhsr.xmax &&
               ymin == rhsr.ymin &&
               ymax == rhsr.ymax;
    }

    void Rectangle::setXmin(long xmin) {
        Rectangle::xmin = xmin;
    }

    void Rectangle::setXmax(long xmax) {
        Rectangle::xmax = xmax;
    }

    void Rectangle::setYmin(long ymin) {
        Rectangle::ymin = ymin;
    }

    void Rectangle::setYmax(long ymax) {
        Rectangle::ymax = ymax;
    }

    std::vector<Rectangle> Rectangle::difference(const Rectangle &other) const {
        std::vector<Rectangle> rectangles;

        Rectangle intersection = intersect(other);
        if (intersection.computeArea() == 0) {
            rectangles.push_back(*this);
            return rectangles;
        }


        if (intersection.getXmin() > xmin) {
            rectangles.emplace_back(xmin, intersection.getXmin(), ymin, ymax);
        }

        if (intersection.getXmax() < xmax) {
            rectangles.emplace_back(intersection.getXmax(), xmax, ymin, ymax);
        }

        if (intersection.getYmin() > ymin) {
            rectangles.emplace_back(intersection.getXmin(), intersection.getXmax(), ymin, intersection.getYmin());
        }

        if (intersection.getYmax() < ymax) {
            rectangles.emplace_back(intersection.getXmin(), intersection.getXmax(), intersection.getYmax(), ymax);
        }

        return rectangles;
    }

    std::ostream &operator<<(std::ostream &os, const Rectangle &rectangle) {
        os << " [xmin: " << rectangle.xmin << ", xmax: " << rectangle.xmax
           << ", ymin: " << rectangle.ymin << ", ymax: " << rectangle.ymax << "]";
        return os;
    }


}


