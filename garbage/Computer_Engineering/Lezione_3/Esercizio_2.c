
Boolean main(){
	int q [2];
	int k [2];
	
	//controllo se sono posizioni valide;

	if(q[0]==k[0])
		return TRUE;
	if(q[1]==k[1])
		return TRUE;
	for(int i=-8;i<8;i++){
			if(q[0]+i==k[0]&&q[1]+i==k[1])
				return TRUE;
			if(q[0]+i==k[0]&&q[1]-i==k[1])
				return TRUE;

	}
	return FALSE;
}
