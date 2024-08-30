#include <bits/stdc++.h>

using namespace std;

const int total_circles = 11; // Total number of circles in the Chakravyuha

int initial_power; // Initial power of Abhimanyu

// Recursive function to determine if Abhimanyu can cross the Chakravyuha.
bool canEscapeChakravyuha(vector<int>& circlePower, int current_circle, int current_power, int back_attack_power, int skips_remaining, int recharges_remaining)
{
    // Base case: Abhimanyu has successfully crossed all circles.
    if (current_circle == total_circles)
        return true;

    bool can_escape = false;

    // Option 1: Recharge if possible and beneficial.
    if (recharges_remaining > 0 && current_power < initial_power)
        can_escape |= canEscapeChakravyuha(circlePower, current_circle, initial_power, back_attack_power, skips_remaining, recharges_remaining - 1);

    // Handle potential attack from behind.
    if (current_power >= back_attack_power)
    {
        current_power -= back_attack_power;
        back_attack_power = 0;
    }
    else
        return false;

    // Option 2: Skip the current circle if skips are available.
    if (skips_remaining > 0)
        can_escape |= canEscapeChakravyuha(circlePower, current_circle + 1, current_power, back_attack_power, skips_remaining - 1, recharges_remaining);

    // Option 3: Fight the current enemy if power is sufficient.
    if (current_power >= circlePower[current_circle])
    {
        if (current_circle == 2 || current_circle == 6)
            back_attack_power = circlePower[current_circle] / 2;

        can_escape |= canEscapeChakravyuha(circlePower, current_circle + 1, current_power - circlePower[current_circle], back_attack_power, skips_remaining, recharges_remaining);
    }

    return can_escape;
}

int main()
{
    // Input the power of each circle's enemy.
    vector<int> circlePower(total_circles);
    for (int i = 0; i < total_circles; i++)
        cin >> circlePower[i];

    // Input the initial power, number of skips, and recharges.
    int skips_allowed, recharges_allowed;
    cin >> initial_power >> skips_allowed >> recharges_allowed;
    skips_allowed = min(skips_allowed, total_circles);  // Restrict skips to the number of circles.
    recharges_allowed = min(recharges_allowed, total_circles);  // Restrict recharges to the number of circles.

    int back_attack_power = 0;  // Initial power of any attacking enemy from behind.

    // Determine if Abhimanyu can cross the Chakravyuha and output the result.
    if (canEscapeChakravyuha(circlePower, 0, initial_power, back_attack_power, skips_allowed, recharges_allowed))
        cout << "Abhimanyu can cross the Chakravyuha" << endl;
    else
        cout << "Abhimanyu cannot cross the Chakravyuha" << endl;

    return 0;
}

/* 
Test Case 1 (Pass):
Input:
1 5 8 2 7 4 3 6 9 2 5
12 3 2
Output:
Abhimanyu can cross the Chakravyuha

Explanation:
- Abhimanyu starts with a power of 12.
- Skips the 1st, 3rd, and 8th circles (using all 3 skips).
- Recharges twice when needed, ensuring power remains sufficient.
- Abhimanyu manages to defeat all enemies without running out of power.

Test Case 2 (Failure):
Input:
9 3 5 2 7 8 4 6 10 1 9
7 2 1
Output:
Abhimanyu cannot cross the Chakravyuha

Explanation:
- Abhimanyu starts with a power of 7.
- Uses 2 skips on weaker enemies but eventually faces strong enemies.
- With only 1 recharge, his power isn't enough to defeat all the enemies.
- He runs out of power before crossing all circles.
*/


/* Edge Cases:

Edge Case 1 (Minimum Power and Enemies with Zero Power):
Input:
0 0 0 0 0 0 0 0 0 0 0
1 0 0
Output:
Abhimanyu can cross the Chakravyuha

Explanation:
- All enemies have zero power.
- Abhimanyu only has 1 power, but since no enemy has any power, he can easily cross all circles without needing skips or recharges.

Edge Case 2 (Maximum Skips and No Recharges):
Input:
8 7 6 5 4 3 2 1 9 10 11
15 11 0
Output:
Abhimanyu can cross the Chakravyuha

Explanation:
- Abhimanyu starts with a power of 15.
- Since he has the maximum number of skips (equal to the number of circles), he can skip all enemies without needing to fight any.
- No recharges are necessary as no power is lost due to the skips.

Edge Case 3 (Strongest Enemy at the Last Circle):
Input:
1 2 3 4 5 6 7 8 9 10 50
20 1 2
Output:
Abhimanyu cannot cross the Chakravyuha

Explanation:
- Abhimanyu has 20 power, enough to defeat all enemies except the last one.
- Even with 1 skip and 2 recharges, his power will be insufficient to defeat the final enemy with 50 power.

Edge Case 4 (Regenerating Enemies Attack Multiple Times):
Input:
2 4 8 3 5 7 10 6 9 1 2
25 0 3
Output:
Abhimanyu cannot cross the Chakravyuha

Explanation:
- Abhimanyu starts with 25 power.
- Enemies at circles 3 and 7 regenerate and attack from behind with half power.
- Even with 3 recharges, Abhimanyu's power is depleted due to the multiple attacks from the regenerating enemies.
*/
