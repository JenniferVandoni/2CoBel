//
// Created by nicola on 30/11/17.
//

#ifndef FUSION_FOCALELEMENTARRAYBUILDER_H
#define FUSION_FOCALELEMENTARRAYBUILDER_H

#include <vector>
#include <src/evidential/focal_elements/FocalElement.h>

/**
 * @class FocalElementContainer
 * Container of FocalElement objects.
 */
class FocalElementContainer {


public:

    virtual ~FocalElementContainer() = default;

    /**
     * Clear the container.
     */
    virtual void clear()=0;

    /**
     * Add a new FocalElement to the container.
     * @param elem The FocalElement to be added.
     * @param mass The mass value.
     */
    virtual void push(std::unique_ptr<FocalElement> elem, double mass)=0;

    /**
     * Set the mass value at a given position.
     * @param index The target position.
     * @param mass The new mass value.
     */
    virtual void set(int index, double mass)=0;

    /**
     * Set the mass value of the given FocalElement.
     * @param fe The target FocalElement.
     * @param mass The new mass value.
     */
    virtual void set(const FocalElement &fe, double mass)=0;

    /**
     * Get the mass value of the given FocalElement.
     * @param fe The target FocalElement
     * @return The associated mass value
     */
    virtual double get(const FocalElement &fe)=0;

    /**
     * Erase the FocalElement at the given position.
     * @param index The target position.
     */
    virtual void erase(int index)=0;

    /**
     * Erase the given FocalElement.
     * @param fe The target FocalElement.
     */
    virtual void erase(const FocalElement &fe)=0;

    /**
     * Get the array of FocalElement object.
     * @return Array of FocalElement.
     */
    virtual const std::vector<std::unique_ptr<FocalElement>> &getFocalElementsArray()=0;

    /**
     * Ge the array of masses.
     * @return Array of masses.
     */
    virtual const std::vector<double> &getMassArray()=0;
};

#endif //FUSION_FOCALELEMENTARRAYBUILDER_H