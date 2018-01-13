#pragma once

// Encodes a combination of render features.
typedef unsigned int RenderFeatureList;

enum RenderResolution
{
    // Render at full resolution
    RS_FullRes = 0,
    
    // Render at (w/2, h/2)
    RS_HalfRes = 1,
    
    // Render at (w/4, h/4)
    RS_QuarterRes = 2,
    
    // Render at (w/8, h/8)
    RS_EighthRes = 3,
    
    // Render at (w/16, h/16)
    RS_SixteenthRes = 4,
};

enum RenderComponent
{
    // Is direct illumination enabled
    RC_Direct = 1,
    
    // Is impulse scattering enabled
    RC_Impulse = 2,
    
    // Is indirect illumination enabled
    RC_Indirect = 4,
    
    // Are shadow rays enabled
    RC_Shadows = 8,
    
    // Are the spheres in the middle of the scene visible
    RC_Spheres = 16,
};

typedef unsigned int RenderComponentList;

enum RenderOverlay
{
    RO_None,
    
    // Visualization of pixel rays
    RO_PixelRays,
    
    // Visualization of the distance to the first hit
    RO_Distance,
    
    // Visualization of hit position
    RO_Position,
    
    // Visualization of diffuse color
    RO_Color,
    
    // Visualization of normals
    RO_Normals,
    
    // Visualization of surface emission values
    RO_Emission,
};
