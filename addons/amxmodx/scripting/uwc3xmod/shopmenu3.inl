/*
SHOPMENU 3
*/

public Set_Shopmenu3_Prices ( )
{
	if ( CVAR_SM3_PRICE_HEAL )
	{
		itemcost3[HEAL-1] = CVAR_SM3_PRICE_HEAL;
	}

	if ( CVAR_SM3_PRICE_INVIS )
	{
		itemcost3[INVIS-1] = CVAR_SM3_PRICE_INVIS;
	}

	if ( CVAR_SM3_PRICE_INVUL )
	{
		itemcost3[INVUL-1] = CVAR_SM3_PRICE_INVUL;
	}

	if ( CVAR_SM3_PRICE_GATE )
	{
		itemcost3[GATE-1] = CVAR_SM3_PRICE_GATE;
	}

	if ( CVAR_SM3_PRICE_DISEASE )
	{
		itemcost3[DISEASE-1] = CVAR_SM3_PRICE_DISEASE;
	}

	if ( CVAR_SM3_PRICE_POISON )
	{
		itemcost3[POISON-1] = CVAR_SM3_PRICE_POISON;
	}

	if ( CVAR_SM3_PRICE_FIRE )
	{
		itemcost3[FIRE-1] = CVAR_SM3_PRICE_FIRE;
	}

	if ( CVAR_SM3_PRICE_ROTITEM )
	{
		itemcost3[ROTITEM-1] = CVAR_SM3_PRICE_ROTITEM;
	}

	if ( CVAR_SM3_PRICE_DEHEX )
	{
		itemcost3[DEHEX-1] = CVAR_SM3_PRICE_DEHEX;
	}
}

public Set_Shopmenu3_Values ( )
{

}


//shopmenu3
public ShopMenu3 ( id )
{
	if ( !uwc3x )
		return PLUGIN_CONTINUE;
	new pos = 0;
	new keys = (1<<0|1<<1|1<<2|1<<3|1<<4|1<<5|1<<6|1<<7|1<<8|1<<9);
	new menu_body[512];
	
	pos += format( menu_body[pos], 511 - pos, "\yBuy a Protection\R$ Cost^n^n" );
	
	for ( new i = 0; i < 9; i++ )
	{
		pos += format( menu_body[pos], 511 - pos, "\w%d. %s\y\R%d^n", i + 1, itemname3[i], itemcost3[i] );
	}
	
	pos += format( menu_body[pos], 511 - pos, "^n\w0. %L", id, "EXIT" );
	show_menu( id, keys, menu_body, -1 );
	return PLUGIN_HANDLED;
}
public Buy_Item3( id , key )
{
	if ( CVAR_DEBUG_MODE )
	{
        	log_amx( "[UWC3X] Debug:: In Buy_item3 : id=%d key=%d", id, key );
	}

	if ( !uwc3x )
		return PLUGIN_CONTINUE;

	if ( !Shopmenu_canBuy ( id , 3 , key ) )
	{
		return PLUGIN_HANDLED;
	}

	playeritem3[id] = key + 1;

	new parm2[2];
	parm2[0] = id;
	parm2[1] = 1;

	if( playeritem3[id] == HEAL)
	{
		set_user_health ( id, get_user_health ( id ) + 50 );

		if ( get_user_health ( id ) > maxhealth[id] )
		{
			set_user_health ( id, maxhealth[id] );
		}

		if( Util_Should_Msg_Client(id) )
		{
			set_hudmessage(0, 255, 255, 0.0, 0.55, 0, 6.0, 3.0, 0.1, 0.2, 1); 
           		show_hudmessage(id, "%L", id, "SM3_HEAL", MOD);
			if ( file_exists( "sound/uwc3x/shopmenu/sm3_heal.wav" ) == 1 )
			{
				emit_sound( id, CHAN_STATIC, "uwc3x/shopmenu/sm3_heal.wav", 1.0, ATTN_NORM, 0, PITCH_NORM );
			}	
		}
	}

	if( playeritem3[id] == INVIS)
	{ 
		set_entity_visibility ( id, 0 );
		new parm[2];
		parm[0] = id;
		parm[1] = INVIS;

		//Play sound and show text
		if( Util_Should_Msg_Client(id) )
		{
			set_hudmessage(0, 255, 255, 0.0, 0.55, 0, 6.0, 3.0, 0.1, 0.2, 1);
            		show_hudmessage(id, "%L", id, "SM3_INVIS", MOD);
			if ( file_exists( "sound/uwc3x/shopmenu/sm3_inv.wav" ) == 1 )
			{
				emit_sound( id, CHAN_STATIC, "uwc3x/shopmenu/sm3_inv.wav", 1.0, ATTN_NORM, 0, PITCH_NORM );
			}
		}
		
		//reset via task in 10 seconds
		parm2[1] = 3;
		set_task( 10.0, "Task_Reset_Shopmenu3", SHOPMENU3_RESET + id, parm2, 2);	
	}

	if( playeritem3[id] == INVUL)
	{
		parm2[1] = 2;
		set_task( 20.0, "Task_Reset_Shopmenu3", SHOPMENU3_RESET + id, parm2, 2);
		if( Util_Should_Msg_Client(id) )
		{
			set_hudmessage(0, 255, 255, 0.0, 0.55, 0, 6.0, 5.0, 0.1, 0.2, 1);
            		show_hudmessage(id, "%L", id, "SM3_INVUL", MOD);
			if ( file_exists( "sound/uwc3x/shopmenu/sm3_invul.wav" ) == 1 )
				emit_sound( id, CHAN_STATIC, "uwc3x/shopmenu/sm3_invul.wav", 1.0, ATTN_NORM, 0, PITCH_NORM );
		}
	}

	if( playeritem3[id] == GATE)
	{
		new parm[2];
		parm[0] = id;
		parm[1] = GATE;

		// Call the front end to the gate routine
		if( Util_Should_Msg_Client(id) )
		{
			set_hudmessage(0, 255, 255, 0.0, 0.55, 0, 6.0, 3.0, 0.1, 0.2, 1);
            		show_hudmessage(id, "%L", id, "SM3_GATE", MOD);
			if ( file_exists( "sound/uwc3x/shopmenu/sm3_gate.wav" ) == 1 )
			{
				emit_sound( id, CHAN_STATIC, "uwc3x/shopmenu/sm3_gate.wav", 1.0, ATTN_NORM, 0, PITCH_NORM );
			}
		}
		Do_Gate_Shopmenu ( id );
	}

	if( playeritem3[id] == DISEASE)
	{
		if ( isdiseasedcb[id] )
		{
			// cure disease
			isdiseasedcb[id] = 0;
			if( Util_Should_Msg_Client(id) )
			{
				set_hudmessage(0, 255, 255, 0.0, 0.55, 0, 6.0, 5.0, 0.1, 0.2, 1);
                		show_hudmessage(id, "%L", id, "SM3_DISEASE", MOD);
				if ( file_exists( "sound/uwc3x/shopmenu/sm3_cure.wav" ) == 1 )
				{
					emit_sound( id, CHAN_STATIC, "uwc3x/shopmenu/sm3_cure.wav", 1.0, ATTN_NORM, 0, PITCH_NORM );
				}
			}
		}
	}

	if( playeritem3[id] == POISON)
	{
		if ( ispoisonedss[id] )
		{
			// cure poison
			ispoisonedss[id] = 0;
			if( Util_Should_Msg_Client(id) )
			{
				set_hudmessage(0, 255, 255, 0.0, 0.55, 0, 6.0, 5.0, 0.1, 0.2, 1);
                		show_hudmessage(id, "%L", id, "SM3_POISON", MOD);
				if ( file_exists( "sound/uwc3x/shopmenu/sm3_cure.wav" ) == 1 )
				{
					emit_sound( id, CHAN_STATIC, "uwc3x/shopmenu/sm3_cure.wav", 1.0, ATTN_NORM, 0, PITCH_NORM );
				}
			}
		}
	}

	if( playeritem3[id] == FIRE)
	{
		if ( ( isburning[id] == 1 ) || (isnburning[id] == 1 ) )
		{
			// cures burns
			isburning[id] = 0;
			isnburning[id] = 0;
			if( Util_Should_Msg_Client(id) )
			{
				set_hudmessage(0, 255, 255, 0.0, 0.55, 0, 6.0, 5.0, 0.1, 0.2, 1);
                		show_hudmessage(id, "%L", id, "SM3_FIRE", MOD);
				if ( file_exists( "sound/uwc3x/shopmenu/sm3_fire.wav" ) == 1 )
				{
					emit_sound( id, CHAN_STATIC, "uwc3x/shopmenu/sm3_fire.wav", 1.0, ATTN_NORM, 0, PITCH_NORM );
				}
			}
		}
	}

	if( playeritem3[id] == ROTITEM)
	{
		if ( bIsRotting[id] )
		{
			// cures burns
			bIsRotting[id] = false;
			if( Util_Should_Msg_Client(id) )
			{
				set_hudmessage(0, 255, 255, 0.0, 0.55, 0, 6.0, 5.0, 0.1, 0.2, 1);
                		show_hudmessage(id, "%L", id, "SM3_ROT", MOD);
				if ( file_exists( "sound/uwc3x/shopmenu/sm3_cure.wav" ) == 1 )
				{
					emit_sound( id, CHAN_STATIC, "uwc3x/shopmenu/sm3_cure.wav", 1.0, ATTN_NORM, 0, PITCH_NORM );
				}
			}
		}
	}

	if( playeritem3[id] == DEHEX)
	{
		// They are hexed, so remove the jumping task
		if ( task_exists ( 2000 + id ) )
		{
			// Removes hex jumping
			remove_task ( 2000 + id );
		}

		// Change their skin back to normal 
		if ( playeritem2[id]!= CHAMELEON )
		{
			changeskin ( id, 1 );
		}
		else
		{
			changeskin ( id, 0 );
		}

		if( Util_Should_Msg_Client(id) )
		{
			set_hudmessage(0, 255, 255, 0.0, 0.55, 0, 6.0, 5.0, 0.1, 0.2, 1);
            		show_hudmessage(id, "%L", id, "SM3_NOHEX", MOD);
			if ( file_exists( "sound/uwc3x/shopmenu/sm3_dehex.wav" ) == 1 )
			{
				emit_sound( id, CHAN_STATIC, "uwc3x/shopmenu/sm3_dehex.wav", 1.0, ATTN_NORM, 0, PITCH_NORM );
			}

		}
	}

	playeritem3[id] = 0;
	cs_set_user_money( id , cs_get_user_money( id ) - itemcost3[key] , 1 );
	playerCanBuyitem3[id] = 0;

	//In 30 seconds, they can rebuy
	parm2[1] = 1;
	set_task( 30.0, "Task_Reset_Shopmenu3", SHOPMENU3_RESET + id, parm2, 2);

	
	displaylevel( id , 3 );
	return PLUGIN_HANDLED;
}
//itemsinfo3 ( id )
public Show_Items_Info3 ( id )
{
	if ( !uwc3x )
		return PLUGIN_CONTINUE;

	new temp[1024] , pos = 0;
	pos += format( temp[pos] , 1024-pos , "<body bgcolor = #000000><font color = #FFB000>" );
	pos += format( temp[pos] , 1024-pos, "%L", id, "SHOPMENU3_HEADER" );
	pos += format( temp[pos], 1024-pos, "<li>%L</li>" , id, "SHOPMENU3_ITEM1" );
	pos += format( temp[pos], 1024-pos, "<li>%L</li>" , id, "SHOPMENU3_ITEM2" );
	pos += format( temp[pos], 1024-pos, "<li>%L</li>" , id, "SHOPMENU3_ITEM3" );
	pos += format( temp[pos], 1024-pos, "<li>%L</li>" , id, "SHOPMENU3_ITEM4" );
	pos += format( temp[pos], 1024-pos, "<li>%L</li>" , id, "SHOPMENU3_ITEM5" );
	pos += format( temp[pos], 1024-pos, "<li>%L</li>" , id, "SHOPMENU3_ITEM6" );
	pos += format( temp[pos], 1024-pos, "<li>%L</li>" , id, "SHOPMENU3_ITEM7" );
	pos += format( temp[pos], 1024-pos, "<li>%L</li>" , id, "SHOPMENU3_ITEM8" );
	pos += format( temp[pos], 1024-pos, "<li>%L</li></ul>" , id, "SHOPMENU3_ITEM9" );
 
	show_motd( id, temp, "Shopmenu3 Item Information" );
	return PLUGIN_CONTINUE;
}


