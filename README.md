# Knapsack_with_genetic_algorithm
Assignment1 in Genetic Algorithms(Soft computing) , implement a genetic algorithm to solve the knapsack problem

# Assignment Description:
   The knapsack problem is a very well-known 
  optimization problem. Given a knapsack that can 
  carry weights up to a certain amount, and a number 
  of items; each item has a weight and a value, we 
  want to select the items to carry in the knapsack in 
  order to maximize the total value.
## What you are required to do:
  Write a genetic algorithm to solve the knapsack
  problem.
  
## What the input looks like:
  You’ll be given an input file with the following format:
  - First line: Number of test cases (must be at least 1)
  For each test case:
  - Size of the knapsack
  - Number of items
     , For each item:
       - Weight and value separated by space
       
       
## Example:
  ![Capture](https://user-images.githubusercontent.com/60941223/224572048-b0921ad1-d881-4154-93bb-5af9fb1975de.JPG)
  
## Important remarks:
  - Use a binary, one-dimensional chromosome.
  - The population size and initialization method you use are up to you. You can 
    actually try different population sizes to see how this will affect your results. The 
    maximum number of generations is also up to you.
  - Think about how you will handle infeasible solutions. Infeasible solutions are 
    solutions that violate the constraints of the problem; therefore, they are not 
    allowed.
  - Use rank selection and one-point crossover. Choose the methods of mutation 
    and replacement that you find appropriate.
  - The output should consist of the test case index, the number of selected items, the 
    total value, and the weight and value of each selected item.
