#include "bubblecollider.hpp"
#include <iostream>
#include <sstream>

void BubbleCollider::resolveCollisions(BubbleData bubbleData, const std::vector<glm::vec2>& lastPositions, const std::vector<glm::vec2>& lastVelocities) const
{
    for(int32_t bubbleAIndex = 0; bubbleAIndex < bubbleData.bubbleAmount; bubbleAIndex++)
    {
        glm::vec2 lastPosA = lastPositions[bubbleAIndex];
        glm::vec2 lastVelA = lastVelocities[bubbleAIndex];
        float radiusA = bubbleData.radiuses[bubbleAIndex];

        for(int32_t bubbleBIndex = bubbleAIndex + 1; bubbleBIndex < bubbleData.bubbleAmount; bubbleBIndex++)
        {
            glm::vec2 lastPosB = lastPositions[bubbleBIndex];
            glm::vec2 lastVelB = lastVelocities[bubbleBIndex];
            float radiusB = bubbleData.radiuses[bubbleBIndex];

            float centerDistance = glm::distance(lastPosA, lastPosB);

            //-----move out overlapping circles-----
            if(centerDistance < radiusA + radiusB)
            {
                bool aIsStatic = bubbleData.staticBodyBools[bubbleAIndex]; 
                bool bIsStatic = bubbleData.staticBodyBools[bubbleBIndex]; 

                glm::vec2 aToBDirection = glm::normalize(lastPosB - lastPosA);

                //move slightly out from each other
                if(!aIsStatic)
                    bubbleData.positions[bubbleAIndex] += -aToBDirection * 0.5f;
                if(!bIsStatic)
                    bubbleData.positions[bubbleBIndex] +=  aToBDirection * 0.5f;
            }
            //-----end move out-----

            //We need the velocity of A as relative to B's velocity so that B can be considered static
            //this is done by adding the reverse velocity of B to A

            glm::vec2 relativeVelA = lastVelA + -lastVelB;

            //std::stringstream info;

            //info << "---Collision procedure---\n";

            //info << "A radius: " << radiusA << "\n";
            //info << "A going from: " << lastPosA << " to " << lastPosA + relativeVelA << "\n";
            //info << "A relative vel: " << relativeVelA << "\n";

            //info << "B radius: " << radiusB << "\n";
            //info << "B static position: " << lastPosB << "\n";

            //step 1: Check that A travelled far enough to even possibly hit B
            //
            // If the movement vector of A is shorter than the distance of the spheres minus their radiuses, there can be no collision

            //info << "distance between balls: " << centerDistance << "\n";

            float relativeVelAMag = glm::length(relativeVelA);

            //info << "relative velocity magnitude " << relativeVelAMag << "\n";

            if(relativeVelAMag < centerDistance - radiusA - radiusB)
            {
                //std::cout << "too far away, no collision possible\n";
                continue;
            }

            //std::cout << "passed 1st \n" << info.str();

            //info.clear();
            //info.str("");

            //step 2: Check that A is travelling in a direction towards B
            //
            // If the dot product of the movement vector of A and the vector from A to B is not positive, then A is not moving towards B
            glm::vec2 fromAToB = lastPosB - lastPosA;

            //info << "a to b vec: " << fromAToB << "\n";
            //info << "a to b vec dot: " << glm::dot(fromAToB, relativeVelA) << "\n";

            if(glm::dot(fromAToB, relativeVelA) <= 0.0f)
            {
                //std::cout << "not moving towards each other, no collision possible\n";
                //std::cout << "failed 2nd \n" << info.str();
                continue;
            }

            //std::cout << "passed 2nd \n" << info.str();

            //info.clear();
            //info.str("");

            //step 3: Check that they overlap when A is on the closest position to B
            //
            // The closest point is calculated through the dot product and pythagoras' theorem, and the radiuses are subsequently compared

            float distanceToClosestPoint = glm::dot(fromAToB, glm::normalize(relativeVelA));
            float radiusSumSquared = std::pow(radiusA + radiusB, 2.0f);
            float closestDistanceSquared = std::pow(centerDistance, 2.0f) - std::pow(distanceToClosestPoint, 2.0f);

            //info << "distance to closest point: " << distanceToClosestPoint << "\n";
            //info << "radius sum squared: " << radiusSumSquared << "\n";
            //info << "closestDistanceSquared: " << closestDistanceSquared << "\n";

            if(closestDistanceSquared > radiusSumSquared)
            {
                //std::cout << "closed point is still too far, no collision possible\n";
                //std::cout << "failed 3rd \n" << info.str();
                continue;
            }

            //std::cout << "passed 3rd \n" << info.str();

            //info.clear();
            //info.str("");

            //step 4: Find the point where they would collide along the current velocity
            // This point is also calculated using pythagoras's theorem - based on the sum of the radiuses and the distance at the shortest point
            // This is then subtracted from the entire distance

            float distanceFromCollisionPointToShortestPoint = radiusSumSquared - closestDistanceSquared;
            float distanceTravelledForCollision = centerDistance - distanceFromCollisionPointToShortestPoint;

            //info << "distance travelled for collision: " << distanceTravelledForCollision << "\n";

            //step 5: Make sure that it actually travels far enough to meet the collision point 
            //
            if(relativeVelAMag < distanceTravelledForCollision)
            {
                //std::cout << "Not travelling far enough, no collision possible\n";
                //std::cout << "failed 4th \n" << info.str();
                continue;
            }

            //step 6: Now we have a collision! Use the distance to the collision point and the total distance to travel to find a percentage on when during the progress the collision happened
            //This percentage is used to advance the velocity correctly.
            
            //std::cout << "passed 4th \n" << info.str();

            //info.clear();
            //info.str("");

            float collisionPercentage = relativeVelAMag / distanceTravelledForCollision;

            //info << "collisionPercentage: " << collisionPercentage << "\n";
            //
            bubbleData.positions[bubbleAIndex] += lastVelA * collisionPercentage;
            bubbleData.positions[bubbleBIndex] += lastVelB * collisionPercentage;

            //info << "\n";

            //std::cout << info.str();
            
            //---Collision response---
            bool aIsStatic = bubbleData.staticBodyBools[bubbleAIndex]; 
            bool bIsStatic = bubbleData.staticBodyBools[bubbleBIndex]; 
            float massA = aIsStatic ? 100000000000.0f : radiusA * radiusA * glm::pi<float>();//bubbleData.masses[bubbleAIndex];
            float massB = bIsStatic ? 100000000000.0f : radiusB * radiusB * glm::pi<float>();//bubbleData.masses[bubbleBIndex];

            glm::vec2 normalizedAtoB = glm::normalize(fromAToB);

            float colMagA = glm::dot(lastVelA, normalizedAtoB);
            float colMagB = glm::dot(lastVelB, normalizedAtoB);

            float optimizedP = (2.0f * (colMagA - colMagB)) / (massA + massB);

            bubbleData.velocities[bubbleAIndex] = lastVelA - optimizedP * massB * normalizedAtoB;
            bubbleData.velocities[bubbleBIndex] = lastVelB + optimizedP * massA * normalizedAtoB;
        }
    }
}
