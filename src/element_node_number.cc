int element_node_number(int shape, int element_type)
{//here shape is the edge node number
	int nen = 0;
	if (shape == 0 && element_type == 2)
	{//linear triangle
		nen = 3;
	}else if (shape == 0 && element_type == 3)
	{//linear quad
		nen = 4;
	}else if (shape == 1 && element_type == 2)
	{//quadratic tri
		nen = 6;
	}else if (shape == 1 && element_type == 3)
	{//quadratic quad
		nen = 9;
	}
	return nen;
}