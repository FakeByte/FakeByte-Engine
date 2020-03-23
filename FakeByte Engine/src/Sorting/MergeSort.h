namespace Sorting{

	//is_pointer a function that returns a bool, depending on the function if the T is a pointer
	//check to see if a * is used
	 template<typename T>
	 struct is_pointer {static const bool value = false;};

	 //If T is a pointer
	 template<typename T>
	 struct is_pointer<T*>{static const bool value  = true;};

	 /**
	 * Merge is called when by the MergeSort function which is for merging the vector that were separated for sorting
	 * If value is smaller than the middle point then it is put on the "Right" vector while larger ones goes to the "Left" vector
	 *
	 * @param left Is where the left vector with larger than pivot values goes
	 * @param right Is where the right vector with smaller than pivot values goes
	 */
	 template<typename T>
	 std::vector<T>Merge(std::vector<T>left,std::vector<T>right) 
		 {
		  size_t iLeft = 0, iRight = 0;
		  std::vector<T>results;

		  if(is_pointer<T>::value)								//Checks if it's a function/operation with pointers
			  {
			   while(iLeft< left.size() && iRight < right.size())	//Loops through the two vectors
				if(*(left[iLeft]) > *(right[iRight]))				//If larger than the values on the right then place on left
				 results.push_back(left[iLeft++]);
				else
				 results.push_back(right[iRight++]);


		   while(iLeft < left.size())results.push_back(left[iLeft++]);
		   while(iRight < right.size())results.push_back(right[iRight++]);

		   return results;
		  }else{
			 while(iLeft < left.size() && iRight < right.size())
				if(left[iLeft] > right[iRight])
				results.push_back(left[iLeft++]);
			else
			 results.push_back(right[iRight++]);
				 while(iLeft < left.size())results.push_back(left[iLeft++]);
				 while(iRight < right.size())results.push_back(right[iRight++]);
				 return results;
			 }
		 }

		 /** Recursive function for merge sort which separates the array/vector into two separate vectors which will be merged later
		 *	Running time of O(n log n)
		 *
		 * @param arr Is the array/vectors that is going to be sorted
		 */
		 template<typename T>
		 std::vector<T>MergeSort(std::vector<T>&arr) {
			  if(arr.size() <= 1)
			   return arr;
				 int length = arr.size() / 2;

				  std::vector<T> left(arr.begin(),arr.begin() + length);
				  std::vector<T>right(arr.begin() + length,arr.end());

			 return Merge(MergeSort(left), MergeSort(right));
		 }
	}