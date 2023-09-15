//
//  VectorWrapper.h
//  StandardCyborgFusion
//
//  Created by Jacob Roscoe on 9/11/23.
//  Copyright © 2023 Standard Cyborg. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <simd/simd.h>

@interface VectorWrapper : NSObject

@property (nonatomic, assign) simd_float3 vector;

@end
