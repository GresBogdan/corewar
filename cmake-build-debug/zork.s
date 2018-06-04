.name		"Celebration Funebre v0.99pl42"
.comment	"Jour J"
 	 	 	
		  sti r1,r2, %2 	 	 	
		  sti r1,r2, %2 	 	 	
	# 	 	 
	ld 1,r4	
		  xer: zjmp %1 	 	 	
		  zjmp %:xer 	 	 	
 		 zjmp %:xer 	 
