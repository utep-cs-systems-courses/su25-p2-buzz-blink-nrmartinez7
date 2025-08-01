	;; this file changes the next state to the curr state to transition
	
	.global assy_trans
	.extern state 		;state variable from c code
	.extern next_state

assy_trans:
	mov.b &next_state, &state	;transition to next state
	ret
