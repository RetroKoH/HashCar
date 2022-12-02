# HashCar
C++ Data Structures Group project

WORKING CONCEPT
	Topic: Hashing. Our program could include a CarType (our first class object), an IDType (our second class object), and a HashType (our data structure). The CarType would include these members: Year, (int) Make (string), and ID (of type IDType, which would have as its private member an int between 1 and const int MAX_CARS).

	We could use a loop to generate an array of random cars of size MAX_CARS. Our BuildHashTable() function would be designed to read from an array, so we could then create a new HashType, and feed the array of cars into the new hash table using BuildHashTable(). The Hash() function would use the ID (an int) to do the sorting.
Our final output could print the sorted list of cars, along with the number of collisions.
 
	With hashing. We can explore one of the methods brought forth in the text or in the Lab assignments, or we can try an alternate method. See this YouTube playlist for reference: https://www.youtube.com/watch?v=aULjfgOYiZI&list=PLprfEn_dJT08ResHBUWgoS9qXnk29iHoM

I think we should aim for a method that minimizes collisions, but I also think we should steer clear of Random Hash methods, as those perform slower. Chaining lets us use a second data structure, and can help avoid collisions, so it's worth considering.
