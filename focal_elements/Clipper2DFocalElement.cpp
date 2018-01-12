//
// Created by nicola on 17/11/17.
//

#include "Clipper2DFocalElement.h"
#include "ConflictFocalElement.h"


Clipper2DFocalElement::Clipper2DFocalElement(std::vector<Geometry::ClipperPolygon> polygons) : polygons(std::move(
        polygons)) {}

const std::vector<Geometry::ClipperPolygon> &Clipper2DFocalElement::getPolygons() const {
    return polygons;
}

double Clipper2DFocalElement::cardinality() const {
    double sum = 0.0;
    for (auto &&polygon : polygons) {
        sum += polygon.computeArea();
    }
    return sum;
}

std::unique_ptr<FocalElement> Clipper2DFocalElement::clone() const {
    return std::unique_ptr<FocalElement>(new Clipper2DFocalElement(polygons));
}

bool Clipper2DFocalElement::equal_to(FocalElement const &rhs) const {
    return cardinality() == rhs.cardinality() && intersect(rhs)->cardinality() == cardinality();
}

bool Clipper2DFocalElement::is_inside(FocalElement const &rhs) const {
    return cardinality() <= rhs.cardinality() && *intersect(rhs) == *this;
}

std::unique_ptr<FocalElement> Clipper2DFocalElement::do_intersection(FocalElement const &rhs) const {
    auto rhsr = static_cast<const Clipper2DFocalElement &>(rhs);
    ClipperLib::Clipper c;
    for (const auto &polygon : polygons) {
        c.AddPath(polygon.getPolygon(), ClipperLib::ptSubject, true);
    }
    for (const auto &polygon : rhsr.getPolygons()) {
        c.AddPath(polygon.getPolygon(), ClipperLib::ptClip, true);
    }
    ClipperLib::Paths solution;
    c.Execute(ClipperLib::ctIntersection, solution);
    std::vector<Geometry::ClipperPolygon> outvec;
    for (auto &path : solution) {
        outvec.emplace_back(path);
    }

    if (outvec.empty())return std::unique_ptr<FocalElement>(new ConflictFocalElement());
    return std::unique_ptr<FocalElement>(new Clipper2DFocalElement(outvec));
}

std::unique_ptr<FocalElement> Clipper2DFocalElement::do_union(FocalElement const &rhs) const {
    auto rhsr = static_cast<const Clipper2DFocalElement &>(rhs);
    ClipperLib::Clipper c;
    for (const auto &polygon : polygons) {
        c.AddPath(polygon.getPolygon(), ClipperLib::ptSubject, true);
    }
    for (const auto &polygon : rhsr.getPolygons()) {
        c.AddPath(polygon.getPolygon(), ClipperLib::ptClip, true);
    }
    ClipperLib::Paths solution;
    c.Execute(ClipperLib::ctUnion, solution);
    std::vector<Geometry::ClipperPolygon> outvec;
    for (auto &path : solution) {
        outvec.emplace_back(path);
    }
    return std::unique_ptr<FocalElement>(new Clipper2DFocalElement(outvec));
}

std::vector<std::unique_ptr<FocalElement>> Clipper2DFocalElement::getInnerSingletons(int step_size) const {
    std::vector<std::unique_ptr<FocalElement>> singletons;
    for (const auto &polygon : polygons) {
        const ClipperLib::Path &path = polygon.getPolygon();
        int xmin = INT32_MAX, xmax = INT32_MIN, ymin = INT32_MAX, ymax = INT32_MIN;
        for (const auto &point : path) {
            if (point.X < xmin)xmin = (int) point.X;
            else if (point.X > xmax)xmax = (int) point.X;
            if (point.Y < ymin)ymin = (int) point.Y;
            else if (point.Y > ymax)ymax = (int) point.Y;
        }
        for (int x = xmin; x <= xmax; x += step_size) {
            for (int y = ymin; y <= ymax; y += step_size) {
                if (polygon.has_inside(Geometry::Point2D(x, y))) {
                    ClipperLib::Path new_path;
                    new_path << ClipperLib::IntPoint(x, y) << ClipperLib::IntPoint(x, y - 1)
                             << ClipperLib::IntPoint(x + 1, y - 1)
                             << ClipperLib::IntPoint(x + 1, y);
                    std::vector<Geometry::ClipperPolygon> polys;
                    polys.emplace_back(new_path);
                    singletons.push_back(std::unique_ptr<FocalElement>(new Clipper2DFocalElement(polys)));
                }
            }
        }
    }
    return singletons;
}

void Clipper2DFocalElement::print(std::ostream &os) const {
    for (auto &polygon : polygons) {
        os << polygon << std::endl;
    }
}


