stock user_spawn( index )
{
	return spawn(index);
}
stock cmd_target2 ( id,const arg[] ) 
{
	new player = find_player ( "bl", arg );

	if ( player )
	{
		if ( player != find_player ( "blj", arg ) )
		{
			console_print ( id,"There are more clients matching to your argument" );
			return 0;
		}
	}
	else if ( ( player = find_player ( "c",arg ) )==0 && arg[0]=='#' && arg[1] )
	{
		player = find_player ( "k",str_to_num ( arg[1] ) );
	}

	if ( !player )
	{
		console_print ( id, "Client with that name or userid not found" );
		return 0;
	}

	return player;
}

stock ExplodeString ( p_szOutput[][], p_nMax, p_nSize, p_szInput[], p_szDelimiter )
{
	new nIdx = 0, l = strlen ( p_szInput );
	new nLen = ( 1 + copyc ( p_szOutput[nIdx], p_nSize, p_szInput, p_szDelimiter ) );

	while ( ( nLen < l ) && ( ++nIdx < p_nMax ) )
	{
		nLen += ( 1 + copyc ( p_szOutput[nIdx], p_nSize, p_szInput[nLen], p_szDelimiter ) );
	}

	return;
}

stock sq ( num ) 
{
	return ( num * num );
}

stock diff ( num,num2 )
{
	if ( num>num2 )
	{
		return ( num-num2 );
	}
	else
	{
		return ( num2-num );
	}

	return 0;
}

stock str_break ( const String[], Left[], Right[], lMax, rMax )
{
	new bool:quote_flag = false;
	new bool:done_flag = false;
	new left_pos = 0;
	new right_pos = 0;
	new i;
	new hold[] = "'^"x";

	copy ( Left, lMax, "" );
	copy ( Right, rMax, "" );

	for ( i=0; i<=strlen ( String )-1; i++ ) 
	{
		if ( equali ( String[i], "^"", 1 ) ) 
		{
			quote_flag = true;
		}
		else if ( ( equali ( String[i], "^"", 1 ) ) && ( quote_flag ) ) 
		{
			quote_flag = false;
		}

		if ( ( equali ( String[i], " ", 1 ) ) && ( !quote_flag ) && ( !done_flag ) ) 
		{
			done_flag = true;
			i++;
		}

		if ( !done_flag && !equali ( String[i], "^"", 1 ) ) 
		{
			if ( left_pos < lMax ) 
			{
				setc ( Left[left_pos], 1, String[i] )
				if ( equali ( Left[left_pos], "'", 1 ) ) 
				{
					setc ( Left[left_pos], 1, hold[1] );
				}
				left_pos++;
			}
		}
		else
		{
			if ( right_pos < rMax && !equali ( String[i], "^"", 1 ) ) 
			{
				setc ( Right[right_pos], 1, String[i] );

				if ( equali ( Right[right_pos], "'", 1 ) ) 
				{
					setc ( Right[right_pos], 1, hold[1] );
				}

				right_pos++;
			}
		}
	}

	Left[left_pos] = 0;
	Right[right_pos] = 0;

	return true;
}


stock replaceall ( text[], const LEN, const WHAT[], const WITH[] ) 
{
	while ( contain ( text, WHAT ) != -1 )
	{
		server_print ( "replacing a ' ..." );
		replace ( text, LEN, WHAT, WITH );
	}
}

stock getMaxClipAmmo(wpnid)
{
	new clipammo = 0;
	switch (wpnid)
	{
		case CSW_P228 : clipammo = 13;
		case CSW_SCOUT : clipammo = 10;
		case CSW_HEGRENADE : clipammo = 0;
		case CSW_XM1014 : clipammo = 7;
		case CSW_C4 : clipammo = 0;
		case CSW_MAC10 : clipammo = 30;
		case CSW_AUG : clipammo = 30;
		case CSW_SMOKEGRENADE : clipammo = 0;
		case CSW_ELITE : clipammo = 15;
		case CSW_FIVESEVEN : clipammo = 20;
		case CSW_UMP45 : clipammo = 25;
		case CSW_SG550 : clipammo = 30;
		case CSW_GALI : clipammo = 35;
		case CSW_FAMAS : clipammo = 25;
		case CSW_USP : clipammo = 12;
		case CSW_GLOCK18 : clipammo = 20;
		case CSW_AWP : clipammo = 10;
		case CSW_MP5NAVY : clipammo = 30;
		case CSW_M249 : clipammo = 100;
		case CSW_M3 : clipammo = 8;
		case CSW_M4A1 : clipammo = 30;
		case CSW_TMP : clipammo = 30;
		case CSW_G3SG1 : clipammo = 20;
		case CSW_FLASHBANG : clipammo = 0;
		case CSW_DEAGLE : clipammo = 7;
		case CSW_SG552 : clipammo = 30;
		case CSW_AK47 : clipammo = 30;
		case CSW_KNIFE : clipammo = 0;
		case CSW_P90 : clipammo = 50;
	}
	return clipammo;
}

public add_grenade_owner( owner ) 
{
	for ( new i = 0; i < 32; i++ ) 
	{
		if ( grenade[i] == 0 ) 
		{
			grenade[i] = owner;
			return;
		}
	}
}

stock get_grenade_owner() 
{
	new which = grenade[0]
	for ( new i = 1; i < 32; i++ ) 
	{
		grenade[i - 1] = grenade[i];
	}

	grenade[31] = 0;

	return which;
}

//
//Stocks ripped from xtrafun.inc for AMXx
//
//Gets the velocity of an entity */
stock get_entity_velocity(index, velocity[3]) 
{
	new Float:vector[3];
	entity_get_vector(index, EV_VEC_velocity, vector);
	FVecIVec(vector, velocity);
}

//Sets the velocity of an entity
stock set_entity_velocity(index, velocity[3]) 
{
	new Float:vector[3];
	IVecFVec(velocity, vector);
	entity_set_vector(index, EV_VEC_velocity, vector);
}

stock set_rendering2(index, fx=kRenderFxNone, r=255, g=255, b=255, render=kRenderNormal, amount=16)
{
#if defined engine
	return set_rendering(index,fx,r,g,b,render,amount)
#else
	set_pev(index, pev_renderfx, fx);
	new Float:RenderColor[3];
	RenderColor[0] = float(r);
	RenderColor[1] = float(g);
	RenderColor[2] = float(b);
	set_pev(index, pev_rendercolor, RenderColor);
	set_pev(index, pev_rendermode, render);
	set_pev(index, pev_renderamt, float(amount));
	return 1;
#endif
}
