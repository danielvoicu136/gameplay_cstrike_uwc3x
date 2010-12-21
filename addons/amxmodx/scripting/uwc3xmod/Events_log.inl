

public Initialize_LogEvents ( )
{
	// Log events: Requires AMX 0.9.3 or better
	register_logevent ( "event_player_action",		3,	"1=triggered"						);
	register_logevent ( "logevent_round_start",		2,	"1=Round_Start"						);
	register_logevent ( "end_round",				2,	"0=World triggered", "1=Round_End"	);
	register_logevent(	"round_start", 				2, 	"1=Round_Start"						);
	//committed suicide with "world"
}

public Initialize_Think ()
{
	register_think("Effect_Rot","Effect_Rot_Think");

}


// ------- LOG KILL------------
//For Jumpkick
public Event_Log_logKill(id, victim, weaponDescription[] ) 
{
	new namea[32],namev[32],authida[35],authidv[35],teama[16],teamv[16];
	
	//Info On Attacker
	get_user_name(id,namea,31);
	get_user_team(id,teama,15);
	get_user_authid(id,authida,34);
	
	//Info On Victim
	get_user_name(victim,namev,31);
	get_user_team(victim,teamv,15);
	get_user_authid(victim,authidv,34);
	
	//Log This Kill
	if(id != victim) 
	{
		log_message("^"%s<%d><%s><%s>^" killed ^"%s<%d><%s><%s>^" with ^"%s^"", namea,get_user_userid(id),authida,teama,namev,get_user_userid(victim),authidv,teamv, weaponDescription );
	}
	else 
	{
		log_message("^"%s<%d><%s><%s>^" committed suicide with ^"%s^"", namea,get_user_userid(id),authida,teama, weaponDescription );
	}
} 
