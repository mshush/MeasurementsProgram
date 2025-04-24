#ifndef REFTARGETCLASS_H
#define REFTARGETCLASS_H

#include <math.h>
class RefTargetClass
{
public:
    RefTargetClass()
    {

    }
    enum ObjectType {
        CYLINDER,
        SPHERE,
        DIHEDRAL_ANGLE
    };
 /**
 * @brief Sets object type.
 *
 * Possible types:
 * CYLINDER
 * SPHERE
 * DIHEDRAL_ANGLE

 * @param RefTargetClass::ObjectType::Type
 */
    void setObjectType(ObjectType type) {
        m_objectType = type;
    }
    /**
 * @brief Returns object type.
 *
 * Possible types:
 * CYLINDER
 * SPHERE
 * DIHEDRAL_ANGLE

 * @return RefTargetClass::ObjectType::Type.
 */
    ObjectType getObjectType() const {
        return m_objectType;
    }

    void setCylinderParameters(double radius_meters, double height_meters) {
        m_cylinderRadius = radius_meters;
        m_cylinderHeight = height_meters;
    }

    void setSphereParameters(double radius_meters) {
        m_sphereRadius = radius_meters;
    }

/**
 * @brief Calculates the Radar Cross-Section (RCS) for a pre-selected type of object.
 *
 * This function uses the formula
 * RCS_sphere= π × r².
 * RCS_cyl = 2 π r l² / lambda
 * all sizes are in meters

 * @param frequency of calculation (in GHz)
 * @return The calculated RCS value in square meters.
 */
    double calculateRCS(double frequency) {
        switch (m_objectType) {
        case CYLINDER:
            return calculateCylinderRCS(frequency);
        case SPHERE:
            return calculateSphereRCS(frequency);
        default:
            return 0.0; // Unknown object type
        }
    }

private:
    ObjectType m_objectType = ObjectType::CYLINDER;

    double m_cylinderRadius = 1.0;
    double m_cylinderHeight = 1.0;
        double m_sphereRadius = 1.0;
    /**
 * @brief Calculates the Radar Cross-Section (RCS) for a cylinder
 *
 * This function uses the formula
 * RCS_sphere= π × r².
 * RCS_cyl = 2 π r l² / lambda
 * all sizes are in meters

 * @param frequency of calculation (in GHz)
 * @return The calculated RCS value in square meters.
 */
    double calculateCylinderRCS(double frequencyGHz) {
        double wavelength = 0.3 / frequencyGHz;
        return (2 * M_PI * m_cylinderRadius * m_cylinderHeight*m_cylinderHeight) / wavelength;
    }

    double calculateSphereRCS(double frequency) {
        return M_PI * m_sphereRadius * m_sphereRadius;
    }
};

#endif // REFTARGETCLASS_H
