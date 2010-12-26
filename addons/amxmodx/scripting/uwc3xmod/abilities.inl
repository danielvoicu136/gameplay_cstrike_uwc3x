
public ability_wcbless ( id )
{

    if ( !uwc3x )
    {
        return PLUGIN_HANDLED;
    }

    if ( !p_skills[id][SKILLIDX_BLESS] )
    {
        if( Util_Should_Msg_Client(id) )
        {
            client_print ( id, print_chat, "%L", id, "BLESS_UNTRAINED" );
        }

        return PLUGIN_HANDLED;
    }

    if ( freezetime )
    {
        if( Util_Should_Msg_Client(id) )
        {
            set_hudmessage ( 178, 14, 41, -1.0, -0.4, 1, 0.5, 1.7, 0.2, 0.2, 5 );
            show_hudmessage( id , "%L", LANG_PLAYER, "ABILITY_DURING_FREEZETIME" );
        }
        return PLUGIN_HANDLED;
    }

    if ( u_delay )
    {
        if( Util_Should_Msg_Client(id) )
        {
            set_hudmessage ( 178, 14, 41, -1.0, -0.4, 1, 0.5, 1.7, 0.2, 0.2, 5 );
            show_hudmessage ( id, "%L", LANG_PLAYER, "ULTIMATE_DELAY_MESSAGE", CVAR_ULTIMATE_DELAY );
        }
        return PLUGIN_HANDLED;
    }

    new friendID, body;
    get_user_aiming ( id, friendID, body );

    if ( ( 0 < friendID <= MAX_PLAYERS ) && ( friendID != id ) && ( get_user_team ( id ) == get_user_team ( friendID ) ) && is_user_alive ( id ) && is_user_alive ( friendID ) )
    {
        // id has a friendID to check for wounds
        // Number of max blessings
        if ( blessings[id] >= 1 )
        {
            if( Util_Should_Msg_Client(id) )
            {
                client_print ( id, print_chat, "%L", id, "BLESS_MAX_BLESS", MOD );
            }

            return PLUGIN_HANDLED;
        }
        
        
        blessed[friendID] = true;

        new name[32], friend_name[32];
        get_user_name ( id, name, 31 );
        get_user_name ( friendID, friend_name, 31 );

        blessings[id] += 1;

        new xpbonus = 0;

        xpbonus = BLESSXP + xpgiven_lev[p_level[id]];

        if ( CVAR_SAVE_XP )
        {
            xpbonus += ( BLESSXP * p_level[id] );
        }
        
        if ( get_user_armor ( friendID ) <= 0 )
        {
            give_item( friendID , "item_kevlar" );
        }

        if (blessed[friendID] == true )
        {
            maxarmor[friendID] += 30;
            maxhealth[friendID] += 30;
        }
        set_user_health_log ( friendID, maxhealth[friendID] );
        set_user_armor_log ( friendID, maxarmor[friendID] );
        
        //Curing any negative effect on target
        if ( p_skills[id][SKILLIDX_BLESS] >= 1 )
        {
            if ( ispoisonedss[friendID] )
            {
                // Remove any poison from target
                ispoisonedss[friendID] = 0;
            }

            if ( isdiseasedcb[friendID] )
            {
                // Remove any disease from target
                isdiseasedcb[friendID] = 0;
            }

            if ( isburning[friendID] || isnburning[friendID] )
            {
                // Remove any napalm from target
                isburning[friendID] = 0;
                isnburning[friendID] = 0;
            }
        }

        // Award the player XP for their service
        playerxp[id] += xpbonus;

        if( Util_Should_Msg_Client(id) )
        {
            client_print ( id, print_chat, "%L", id, "BLESS_CAST", MOD, friend_name, xpbonus );
            if ( file_exists( "sound/uwc3x/bless.wav" ) == 1 ) 
            {
				emit_sound( id, CHAN_STATIC, "uwc3x/bless.wav", 1.0, ATTN_NORM, 0, PITCH_NORM );
            }
        }

        if( is_user_connected( friendID ) && !is_user_bot(friendID) )
        {
            client_print ( friendID, print_chat, "%L", friendID, "BLESS_GET", MOD, name );
            if ( file_exists( "sound/uwc3x/bless.wav" ) == 1 ) 
            {
                emit_sound( friendID, CHAN_STATIC, "uwc3x/bless.wav", 1.0, ATTN_NORM, 0, PITCH_NORM );
            }
        }
    }
    else if ( Util_Should_Msg_Client_Dead ( id ) )
    {
        client_print ( id, print_chat, "%L", id, "SHHH_DEAD_MESSAGE", MOD );
    }
    
    return PLUGIN_HANDLED;
}

public ability_wcward ( id )
{
	if ( !p_skills[id][SKILLIDX_SERPWARD] )
	{
		if( Util_Should_Msg_Client(id) )
		{
			client_print ( id, print_chat, "%L", id, "SERPENTWARD_UNTRAINED" );
		}
		return PLUGIN_HANDLED;
	}

	if ( is_user_alive ( id ) )
	{
		if ( serpents[id] > 0 && !endround && wardsused[id] < serpents[id] )
		{
			if ( get_user_team ( id )==TEAM_T )
			{
				serpentteam[id]=TEAM_T;
			}
			else
			{
				serpentteam[id]=TEAM_CT;
			}

			new parm[6];
			new origin[3];

			get_user_origin ( id,origin );
			parm[0] = origin[0];
			parm[1] = origin[1];
			parm[2] = origin[2];
			parm[5] = id;
			Draw_SerpentWard_Beam ( parm );

			serpents[id]--;
			wardsused[id]++;

			if( Util_Should_Msg_Client(id) )
			{
				set_hudmessage ( 200, 100, 0, 0.2, 0.3, 0, 1.0, 5.0, 0.1, 0.2, 2 );
				show_hudmessage ( id, "%L", LANG_PLAYER, "SERPENTWARD_PLACED", serpents[id] );
			}
		}
		else
		{
			if( wardsused[id] >= serpents[id] )
			{
				new serpentCount = p_serpent[p_skills[id][SKILLIDX_SERPWARD]-1];
				set_hudmessage ( 200, 100, 0, 0.2, 0.3, 0, 1.0, 5.0, 0.1, 0.2, 2 );
				show_hudmessage ( id, "%L", LANG_PLAYER, "SERPENTWARD_ALLGONE", serpentCount );
			}
		}
	}

	return PLUGIN_HANDLED;
}

//formerly_lightpls
public Draw_SerpentWard_Beam ( parm[6] )
{

	if ( !is_user_alive ( parm[5] ) )
	{
		return PLUGIN_CONTINUE;
	}

	new origin[3], damage, id;
	id = parm[5];

	origin[0] = parm[0];
	origin[1] = parm[1];
	origin[2] = parm[2];

	message_begin ( MSG_BROADCAST, SVC_TEMPENTITY );
	write_byte ( 0 );
	write_coord ( origin[0] );
	write_coord ( origin[1] );
	write_coord ( origin[2] +600 );
	write_coord ( origin[0] );
	write_coord ( origin[1] );
	write_coord ( origin[2] -600 );
	write_short ( lightning );

	// framestart
	write_byte ( 1 );

	// framerate
	write_byte ( 5 );

	// life
	write_byte ( 2 );

	// width
	write_byte ( 500 );

	// noise
	write_byte ( 20 ) ;

	//Set the color of the Serpent ward based on the TeamID
	if ( serpentteam[id] == 1 )
	{
		//Terrorist
		write_byte ( 255 ); // r
		write_byte ( 0 ); // g
		write_byte ( 0 ); // b
	}
	else
	{
		//Counter Terrorist
		write_byte ( 0 ); // r
		write_byte ( 0 ); // g
		write_byte ( 255 ); // b
	}

	// brightness
	write_byte ( 100 );

	// speed
	write_byte ( 100 );

	message_end ( );

	new players[32], numberofplayers, targetorigin[3];
	get_players ( players, numberofplayers );

	new targetid = 0;
	new distancebetween = 0;

	for ( new i = 0; i < numberofplayers; ++i )
	{
		targetid = players[i];

		// [10-30-04] - Necklaces no longer protect against Serpent Wards
		if ( ( serpentteam[id] != get_user_team ( targetid ) ) && is_user_alive ( targetid ) )
		{

			get_user_origin ( targetid,targetorigin );
			distancebetween= sqrt ( ( origin[1] - targetorigin[1] ) * ( origin[1] - targetorigin[1] ) + ( origin[0] - targetorigin[0] ) * ( origin[0] - targetorigin[0] ) );

			if ( ( distancebetween < 85 ) )
			{

				// [08-08-04] - Check if Magic Resistance protects against Ward - K2mia
				if ( Util_IsPlayer_Immune ( targetid , 2 ) )
				{
					if( is_user_connected( targetid ) && !is_user_bot(targetid) )
					{
						client_print ( targetid, print_chat, "%L", targetid, "SERPENTWARD_MAGICPROTECT", MOD );
						continue;
					}
				}

				//DEAL DAMAGE
				damage = 10;
				do_damage ( targetid, id, damage, 14, 3, 0, 0, 0 );

				if( Util_Should_Msg_Client( id ) )
				{

					client_cmd ( targetid, "spk ambience/thunder_clap.wav" );
					message_begin ( MSG_ONE, gmsgFade,{ 0, 0, 0}, id );

					// fade lasts this long duration
					write_short ( 1<<10 );

					// fade lasts this long hold time
					write_short ( 1<<10 );

					// fade type ( in / out )
					write_short ( 1<<12 );

					 // fade red
					write_byte ( 255 );

					// fade green
					write_byte ( 255 );

					// fade blue
					write_byte ( 255 );

					// fade alpha
					write_byte ( iglow[id][3] );

					message_end ( );
				}

				if ( iglow[id][0] < 1 )
				{
					new parm2[2];
					parm2[0] = id;
					set_task ( 0.01, "ChangeGlow", TASK_CHANGE_GLOW2, parm2, 2 );
				}

				iglow[id][0] += 3*damage;
				iglow[id][1] = 0;
				iglow[id][2] = 0;
				iglow[id][3] = 0;

				if ( iglow[id][0] > MAXGLOW )
				{
					iglow[id][0] = MAXGLOW;
				}

				if( Util_Should_Msg_Client( id ) )
				{

					message_begin ( MSG_ONE, gmsgFade, { 0, 0, 0 }, id );

					 // fade lasts this long duration
					write_short ( 1<<10 );

					// fade lasts this long hold time
					write_short ( 1<<10 );

					 // fade type ( in / out )
					write_short ( 1<<12 );

					// fade red
					write_byte ( 255 );

					// fade green
					write_byte ( 0 );


					// fade blue
					write_byte ( 0 );

					// fade alpha
					write_byte ( iglow[id][0] );

					message_end ( );
				}
			}
		}
	}

	if ( !endround )
	{
		set_task ( 0.45, "Draw_SerpentWard_Beam", 43, parm, 6 );
	}

	return PLUGIN_CONTINUE;
}


public ability_wcrepair ( id )
{
	if ( !CVAR_ENABLE_UWC3X )
	{
		return PLUGIN_HANDLED;
	}

	if ( !p_skills[id][SKILLIDX_REPAIR] )
	{
		if( Util_Should_Msg_Client(id) )
		{
			client_print ( id, print_chat, "%L", id, "REPAIR_ARMOR_UNTRAINED" );
		}

		return PLUGIN_HANDLED;
	}

	if ( freezetime )
	{
		if( Util_Should_Msg_Client(id) )
		{
			set_hudmessage ( 178, 14, 41, -1.0, -0.4, 1, 0.5, 1.7, 0.2, 0.2, 5 );
			show_hudmessage( id , "%L", LANG_PLAYER, "ABILITY_DURING_FREEZETIME" );
		}
		return PLUGIN_HANDLED;
	}

	if ( u_delay )
	{
		if( Util_Should_Msg_Client(id) )
		{
			set_hudmessage ( 178, 14, 41, -1.0, -0.4, 1, 0.5, 1.7, 0.2, 0.2, 5 );
			show_hudmessage ( id, "%L", LANG_PLAYER, "ULTIMATE_DELAY_MESSAGE", CVAR_ULTIMATE_DELAY );
		}
		return PLUGIN_HANDLED;
	}

	new friendID, body;
	get_user_aiming ( id, friendID, body );

	if ( ( 0 < friendID <= MAX_PLAYERS ) && ( friendID != id ) && ( get_user_team ( id ) == get_user_team ( friendID ) ) && is_user_alive ( id ) && is_user_alive ( friendID ) )
	{
		// id has a friendID to check for armor repairs
		new max_repairs = 0;

		// Number of max repairs based on player level
		if ( p_level[id] >= 34 )
		{
			max_repairs = 5;
		}
		else if ( p_level[id] > 30 )
		{
			max_repairs = 4;
		}
		else if ( p_level[id] > 20 )
		{
			max_repairs = 3;
		}
		else
		{
			max_repairs = 2;
		}

		if ( repairs[id] >= max_repairs )
		{
			if( Util_Should_Msg_Client(id) )
			{
				client_print ( id, print_chat, "%L", id, "REPAIR_ARMOR_MAX_REPAIRS", MOD );
				return PLUGIN_HANDLED;
			}

		}

		new name[32], friend_name[32];
		get_user_name ( id, name, 31 );
		get_user_name ( friendID, friend_name, 31 );

		if ( get_user_armor ( friendID ) <= 0 || get_user_armor ( friendID ) >= maxarmor[friendID] )
		{
			if( Util_Should_Msg_Client(id) )
			{
				client_print ( id, print_chat, "%L", id, "REPAIR_ARMOR_UNNEEDED", MOD, friend_name );
				return PLUGIN_HANDLED;
			}
		}

		repairs[id] += 1;

		new abonus = 0;
		new xpbonus = 0;

		//FIGURE OUT HOW MUCH ARMOR TO GIVE THE PLAYER
		if ( p_level[id] > 30 )
		{
			abonus = ( 7 * ARMORBONUS1 );
		}
		else if ( p_level[id] > 25 )
		{
			abonus = ( 6 * ARMORBONUS1 );
		}
		else if ( p_level[id] > 20 )
		{
			abonus = ( 5 * ARMORBONUS1 );
		}
		else if ( p_level[id] > 15 )
		{
			abonus = ( 4 * ARMORBONUS1 );
		}
		else if ( p_level[id] > 10 )
		{
			abonus = ( 3 * ARMORBONUS1 );
		}
		else if ( p_level[id] > 5 )
		{
			abonus = ( 2 * ARMORBONUS1 );
		}else{
			abonus = ARMORBONUS1;
		}

		//AWARD XP
		xpbonus = REPAIRXP + xpgiven_lev[p_level[id]];

		if ( CVAR_SAVE_XP )
		{
			xpbonus += ( REPAIRXP * p_level[id] );
		}

		// Award the player XP for their service
		playerxp[id] += xpbonus;

		//set_user_armor ( friendID, get_user_armor ( friendID ) + abonus )
		set_user_armor_log ( friendID, ( get_user_armor ( friendID ) + abonus ) );

		if ( get_user_armor ( friendID ) > maxarmor[friendID] )
		{
			set_user_armor_log ( friendID, maxarmor[friendID] );
		}

		if( Util_Should_Msg_Client(friendID) )
		{
			client_print ( friendID, print_chat, "%L", friendID, "REPAIR_ARMOR_MESSAGE", MOD, name );
			emit_sound(friendID, CHAN_ITEM, "items/suitchargeok1.wav", 1.0, ATTN_NORM, 0, PITCH_NORM);
		}

		if( Util_Should_Msg_Client(id) )
		{
			client_print ( id, print_chat, "%L", id, "REPAIR_ARMOR_XP_MESSAGE", MOD, xpbonus );
			emit_sound(id, CHAN_ITEM, "items/suitchargeok1.wav", 1.0, ATTN_NORM, 0, PITCH_NORM);
		}
	}
	else if ( Util_Should_Msg_Client_Dead ( id ) )
	{
		client_print ( id, print_chat, "%L", id, "SHHH_DEAD_MESSAGE", MOD );
	}

	return PLUGIN_HANDLED;
}

public ability_TeamShieldXP( id, PlayerShieldedBy )
{
	//AWARD XP for team shield
	new xpbonus = SHEILDXP + xpgiven_lev[p_level[id]];

	if ( CVAR_SAVE_XP )
	{
		xpbonus += ( SHEILDXP * p_level[id] );
	}

	new name[32];
	get_user_name ( id, name, 31 );

	if( is_user_connected( PlayerShieldedBy ) && !is_user_bot(PlayerShieldedBy) )
	{
		client_print ( PlayerShieldedBy, print_chat, "%L", PlayerShieldedBy, "ULTIMATE_SIV_XP",  xpbonus, name);
	}

	if ( CVAR_SAVE_XP )
	{
		xpbonus += ( SHEILDXP * p_level[id] );
	}

	// Award the player XP for their service
	playerxp[PlayerShieldedBy] += xpbonus;

}


public ability_wcdispell ( id )
{

	if ( !CVAR_ENABLE_UWC3X )
	{
		return PLUGIN_HANDLED;
	}

	if ( !p_skills[id][SKILLIDX_DISHEX] )
	{
		if( Util_Should_Msg_Client(id) )
		{
			client_print ( id, print_chat, "%L", id, "DISPELL_UNTRAINED" );
		}

		return PLUGIN_HANDLED;
	}

	if ( freezetime )
	{
		if( Util_Should_Msg_Client(id) )
		{
			set_hudmessage ( 178, 14, 41, -1.0, -0.4, 1, 0.5, 1.7, 0.2, 0.2, 5 );
			show_hudmessage( id , "%L", LANG_PLAYER, "ABILITY_DURING_FREEZETIME" );
		}
		return PLUGIN_HANDLED;
	}

	if ( u_delay )
	{
		if( Util_Should_Msg_Client(id) )
		{
			set_hudmessage ( 178, 14, 41, -1.0, -0.4, 1, 0.5, 1.7, 0.2, 0.2, 5 );
			show_hudmessage ( id, "%L", LANG_PLAYER, "ULTIMATE_DELAY_MESSAGE", CVAR_ULTIMATE_DELAY );
		}
		return PLUGIN_HANDLED;
	}

	new friendID, body;
	get_user_aiming ( id, friendID, body );

	if ( ( 0 < friendID <= MAX_PLAYERS ) && ( friendID != id ) && ( get_user_team ( id ) == get_user_team ( friendID ) ) && is_user_alive ( id ) && is_user_alive ( friendID ) )
	{
		// id has a friendID to check for armor repairs
		new max_dispells = 0;

		// Number of max repairs based on player level
		if ( p_level[id] >= 34 )
		{
			max_dispells = 5;
		}
		else if ( p_level[id] > 30 )
		{
			max_dispells = 4;
		}
		else if ( p_level[id] > 20 )
		{
			max_dispells = 3;
		}
		else
		{
			max_dispells = 2;
		}

		if ( dispells[id] >= max_dispells )
		{

			if( Util_Should_Msg_Client(id) )
			{
				client_print ( id, print_chat, "%L", id, "DISPELL_MAX_DISPELLS", MOD );
			}

			return PLUGIN_HANDLED;
		}

		// check their hexed
		new tmpModel[48];
		cs_get_user_model ( friendID, tmpModel, 47 );

		if ( !equali ( tmpModel, "zombie" ) )
		{
			if( Util_Should_Msg_Client(id) )
			{
				client_print ( id, print_chat, "%L", id, "DISPELL_NOT_HEXED", MOD );
			}

			return PLUGIN_HANDLED;
		}

		// They are hexed, so remove the jumping task
		if ( task_exists ( 2000 + friendID ) )
		{
			// Removes hex jumping
			remove_task ( 2000 + friendID );
		}

		// Change their skin back to normal
		if ( playeritem2[friendID]!= CHAMELEON )
		{
			changeskin ( friendID, 1 );
		}
		else
		{
			changeskin ( friendID, 0 );
		}

		dispells[id] += 1;

		new xpbonus = MENDXP + xpgiven_lev[p_level[id]];

		if ( CVAR_SAVE_XP )
		{
			xpbonus += ( DISPELLXP * p_level[id] );
		}

		// Award the player XP for their service
		playerxp[id] += xpbonus;

		new name[32];
		get_user_name ( id, name, 31 );
		
		bHexed[friendID] = false;

		if( Util_Should_Msg_Client(id) )
		{
			client_print ( id, print_chat, "%L", id, "DISPELL_XP_MESSAGE", MOD, xpbonus );
			if ( file_exists( "sound/uwc3x/dispell_hex.wav" ) == 1 )
				emit_sound( id, CHAN_STATIC, "uwc3x/dispell_hex.wav", 1.0, ATTN_NORM, 0, PITCH_NORM );
		}

		if( is_user_connected( friendID ) && !is_user_bot(friendID) )
		{
			client_print ( friendID, print_chat, "%L", friendID, "DISPELL_MESSAGE", MOD, name );
			if ( file_exists( "sound/uwc3x/dispell_hex.wav" ) == 1 )
				emit_sound( friendID, CHAN_STATIC, "uwc3x/dispell_hex.wav", 1.0, ATTN_NORM, 0, PITCH_NORM );
		}
	}
	else if ( Util_Should_Msg_Client_Dead ( id ) )
	{
		client_print ( id, print_chat, "%L", id, "SHHH_DEAD_MESSAGE", MOD );
	}

	return PLUGIN_HANDLED;
}


public ability_wcmend ( id )
{

	if ( !CVAR_ENABLE_UWC3X )
	{
		return PLUGIN_HANDLED;
	}

	if ( !p_skills[id][SKILLIDX_MEND] )
	{
		if( Util_Should_Msg_Client(id) )
		{
			client_print ( id, print_chat, "%L", id, "MENDWOUNDS_UNTRAINED" );
		}

		return PLUGIN_HANDLED;
	}

	if ( freezetime )
	{
		if( Util_Should_Msg_Client(id) )
		{
			set_hudmessage ( 178, 14, 41, -1.0, -0.4, 1, 0.5, 1.7, 0.2, 0.2, 5 );
			show_hudmessage( id , "%L", LANG_PLAYER, "ABILITY_DURING_FREEZETIME" );
		}
		return PLUGIN_HANDLED;
	}

	if ( u_delay )
	{
		if( Util_Should_Msg_Client(id) )
		{
			set_hudmessage ( 178, 14, 41, -1.0, -0.4, 1, 0.5, 1.7, 0.2, 0.2, 5 );
			show_hudmessage ( id, "%L", LANG_PLAYER, "ULTIMATE_DELAY_MESSAGE", CVAR_ULTIMATE_DELAY );
		}
		return PLUGIN_HANDLED;
	}

	new friendID, body;
	get_user_aiming ( id, friendID, body );

	if ( ( 0 < friendID <= MAX_PLAYERS ) && ( friendID != id ) && ( get_user_team ( id ) == get_user_team ( friendID ) ) && is_user_alive ( id ) && is_user_alive ( friendID ) )
	{
		// id has a friendID to check for wounds
		// Number of max mends based on player level
		new max_mends = 0;

		if ( p_level[id] >= 34 )
		{
			max_mends = 5;
		}
		else if ( p_level[id] > 30 )
		{
			max_mends = 4;
		}
		else if ( p_level[id] > 20 )
		{
			max_mends = 3;
		}
		else
		{
			max_mends = 2;
		}

		if ( mends[id] >= max_mends )
		{
			if( Util_Should_Msg_Client(id) )
			{
				//client_print ( id, print_chat, "%L", id, "MENDWOUNDS_MAX_HEALS", MOD );
				HudChatShow(id, "MENDWOUNDS_MAX_HEALS", MOD);
			}

			return PLUGIN_HANDLED;
		}

		new name[32], friend_name[32];
		get_user_name ( id, name, 31 );
		get_user_name ( friendID, friend_name, 31 );

		if ( get_user_health ( friendID ) >= maxhealth[friendID] )
		{
			if( Util_Should_Msg_Client(id) )
			{
				//client_print ( id, print_chat, "%L", id, "MENDWOUNDS_NOT_HURT", MOD, friend_name );
				HudChatShow(id, "MENDWOUNDS_NOT_HURT", MOD, friend_name);
			}

			return PLUGIN_HANDLED;
		}

		mends[id] += 1;

		new hbonus = 0;
		new xpbonus = 0;

		//CALCULATE HOW MUCH TO HEAL THE OTHER PLAYER
		if ( p_level[id] > 30 )
		{
			hbonus = ( 7 * HEALTHBONUS );
		}
		else if ( p_level[id] > 25 )
		{
			hbonus = ( 6 * HEALTHBONUS );
		}
		else if ( p_level[id] > 20 )
		{
			hbonus = ( 5 * HEALTHBONUS );
		}
		else if ( p_level[id] > 15 )
		{
			hbonus = ( 4 * HEALTHBONUS );
		}
		else if ( p_level[id] > 10 )
		{
			hbonus = ( 3 * HEALTHBONUS );
		}
		else if ( p_level[id] > 5 )
		{
			hbonus = ( 2 * HEALTHBONUS );
		}
		else
		{
			hbonus = HEALTHBONUS;
		}

		xpbonus = MENDXP + xpgiven_lev[p_level[id]];

		if ( CVAR_SAVE_XP )
		{
			xpbonus += ( MENDXP * p_level[id] );
		}

		set_user_health ( friendID, get_user_health ( friendID ) + hbonus );

		if ( get_user_health ( friendID ) > maxhealth[friendID] )
		{
			set_user_health ( friendID, maxhealth[friendID] );
		}

		new cured_burns = 0;
		new cured_poison = 0;
		new cured_disease = 0;

		//Stuff that can occur if they have 2 or more points in heal
		if ( p_skills[id][SKILLIDX_MEND] >= 2 )
		{
			if ( ispoisonedss[friendID] )
			{
				// 2nd tier of Mend can cure poison
				ispoisonedss[friendID] = 0;
				cured_poison = 1;
			}

			if ( isdiseasedcb[friendID] )
			{
				// 2nd tier of Mend can cure disease
				isdiseasedcb[friendID] = 0;
				cured_disease = 1;
			}
		}

		//Stuff that can occur if they have 3 or more points in heal
		if ( p_skills[id][SKILLIDX_MEND] >= 3 )
		{
			if ( isburning[friendID] || isnburning[friendID] )
			{
				// 3rd tier cures flamethrower and napalm burns
				isburning[friendID] = 0;
				isnburning[friendID] = 0;
				cured_burns = 1;
			}
		}

		// Handle extra XP bonuses and messages for burns, poison, disease, etc
		if ( cured_burns && cured_poison && cured_disease )
		{
			xpbonus += xplevel_lev[p_level[id]];
			if( Util_Should_Msg_Client(id) )
			{
				//client_print ( id, print_chat, "%L", id, "MENDWOUNDS_CURED_ALL", MOD, friend_name, xpbonus );
				HudChatShow(id, "MENDWOUNDS_CURED_ALL", MOD, friend_name, xpbonus);
			}

			if( is_user_connected( friendID ) && !is_user_bot(friendID) )
			{
				//client_print ( friendID, print_chat, "%L", friendID, "MENDWOUNDS_CURED_ALL_MESSAGE", MOD, name );
				HudChatShow(friendID, "MENDWOUNDS_CURED_ALL_MESSAGE", MOD, name);
			}
		}
		else if ( cured_burns && ( cured_poison || cured_disease ) )
		{
			xpbonus += ( 2 * MENDXP );

			if( Util_Should_Msg_Client(id) )
			{
				//client_print ( id, print_chat, "%L", id, "MENDWOUNDS_CURED_TWO", MOD, friend_name, xpbonus );
				HudChatShow(id, "MENDWOUNDS_CURED_TWO", MOD, friend_name, xpbonus);
			}

			if( is_user_connected( friendID ) && !is_user_bot(friendID) )
			{
				//client_print ( friendID, print_chat, "%L", friendID, "MENDWOUNDS_CURED_TWO_MESSAGE", MOD, name );
				HudChatShow(friendID, "MENDWOUNDS_CURED_TWO_MESSAGE", MOD, name);
			}
		}
		else if ( cured_poison && cured_disease )
		{
			xpbonus += floatround ( 1.5 * MENDXP );

			if( Util_Should_Msg_Client(id) )
			{
				//client_print ( id, print_chat, "%L", id, "MENDWOUNDS_CURED_TWO2", MOD, friend_name, xpbonus );
				HudChatShow(id, "MENDWOUNDS_CURED_TWO2", MOD, friend_name, xpbonus);
			}

			if( Util_Should_Msg_Client(friendID) )
			{
				//client_print ( friendID, print_chat, "%L", friendID, "MENDWOUNDS_CURED_TWO_MESSAGE2", MOD, name );
				HudChatShow(friendID, "MENDWOUNDS_CURED_TWO_MESSAGE2", MOD, name);
			}
		}
		else if ( cured_poison || cured_disease )
		{
			xpbonus += MENDXP;

			if( Util_Should_Msg_Client(id) )
			{
				//client_print ( id, print_chat, "%L", id, "MENDWOUNDS_CURED_ONE", MOD, friend_name, xpbonus );
				HudChatShow(id, "MENDWOUNDS_CURED_ONE", MOD, friend_name, xpbonus);
			}

			if( Util_Should_Msg_Client(friendID) )
			{
				//client_print ( friendID, print_chat, "%L", friendID, "MENDWOUNDS_CURED_ONE_MESSAGE", MOD, name );
				HudChatShow(friendID, "MENDWOUNDS_CURED_ONE_MESSAGE", MOD, name);
			}
		}
		else
		{
			if( Util_Should_Msg_Client(id) )
			{
				HudChatShow(id, "MENDWOUNDS_CURED", MOD, friend_name, xpbonus);
				//client_print ( id, print_chat, "%L", id, "MENDWOUNDS_CURED", MOD, friend_name, xpbonus );
			}

			if( is_user_connected( friendID ) && !is_user_bot(friendID) )
			{
				HudChatShow(friendID, "MENDWOUNDS_CURED_MESSAGE", MOD, name);
				//client_print ( friendID, print_chat, "%L", friendID, "MENDWOUNDS_CURED_MESSAGE", MOD, name );
			}
		}

		// Award the player XP for their service
		playerxp[id] += xpbonus;

		if( Util_Should_Msg_Client(id) )
		{
			emit_sound ( id, CHAN_ITEM, "items/medshot5.wav", 1.0, ATTN_NORM, 0, PITCH_NORM );
		}

	}
	else if ( Util_Should_Msg_Client_Dead ( id ) )
	{
		client_print ( id, print_chat, "%L", id, "SHHH_DEAD_MESSAGE", MOD );
	}

	return PLUGIN_HANDLED;
}



//draw_medicspr
public Draw_Medic_Repair_Sprites ( )
{
	if ( CVAR_MEDIC_ALERTS != 2 )
	{
		return PLUGIN_CONTINUE;
	}

	new players[32], numofplayers, idself, id, i, j, origin[3], wsprite;
	get_players ( players, numofplayers );

	for ( i = 0; i < numofplayers; i++ )
	{
		// Player id to display medic sprites to
		idself = players[i];

		// If idself player is dead skip to next
		if ( !is_user_alive ( idself ) )
		{
			continue;
		}

		new idself_skill = 0;

		// Determine extent of skill ( mend, repair or both )
		if ( ( p_skills[idself][SKILLIDX_MEND] ) && ( p_skills[idself][SKILLIDX_REPAIR] ) )
		{
			idself_skill = 3;
		}
		else if ( p_skills[idself][SKILLIDX_MEND] )
		{
			idself_skill = 1;
		}
		else if ( p_skills[idself][SKILLIDX_REPAIR] )
		{
			idself_skill = 2;
		}
		else
		{
			// If player is not a medic or armorsmith skip to next
			idself_skill = 0;
			continue;
		}

		// If we make it here idself is either medic, armorsmith or both
		// Scan through players and isolate living teammates
		for ( j = 0; j < numofplayers; j++ )
		{
			// Player id to see if medic sprite should be displayed
			id = players[j];

			if ( ( idself != id ) && ( get_user_team ( idself ) == get_user_team ( id ) ) && is_user_alive ( id ) && ( ( get_user_health ( id ) < maxhealth[id] ) || ( get_user_armor ( id ) < maxarmor[id] ) ) )
			{
				//client_print ( idself, print_chat, "evaluating id= ( %d )", id )
				// Determine extent of injury ( health, armor or both )
				new winjury = 0;

				if ( ( get_user_health ( id ) < maxhealth[id] ) && ( get_user_armor ( id ) < maxarmor[id] )  && bIsRotting[id] )
				{
					winjury = 4;
				}
				else
				if ( ( get_user_health ( id ) < maxhealth[id] ) && ( get_user_armor ( id ) < maxarmor[id] ) )
				{
					winjury = 3;
				}
				else if ( get_user_health ( id ) < maxhealth[id] )
				{
					winjury = 1;
				}
				else if ( get_user_armor ( id ) < maxarmor[id] )
				{
					winjury = 2;
				}
				else
				{
					// Player id has no injuries or damaged armor
					continue;
				}

				if ( idself_skill == 3 )
				{
					if ( winjury == 4 )
					{
						wsprite = rotmedshieldspr;
					}
					else if ( winjury == 3 )
					{
						wsprite = medshieldspr;
					}
					else if ( winjury == 1 )
					{
						wsprite = medicspr;
					}
					else if ( winjury == 2 )
					{
						wsprite = shieldspr;
					}
					else
					{
						continue;
					}
				}
				else if ( ( idself_skill == 1 ) && ( ( winjury == 3 ) || ( winjury == 1 ) ) )
				{
					wsprite = medicspr;
				}
				else if ( ( idself_skill == 2 ) && ( ( winjury == 3 ) || ( winjury == 2 ) ) )
				{
					wsprite = shieldspr;
				}
				else
				{
					// Nothing to show for this player -> teammate combo
					continue;
				}

				get_user_origin ( id, origin );

				message_begin ( MSG_ONE, SVC_TEMPENTITY, { 0, 0, 0}, idself );
				write_byte ( TE_PLAYERATTACHMENT );
				write_byte ( id );

				// z axis for sprite
				write_coord ( 30 );

				// which sprite to display
				write_short ( wsprite );
				write_short ( 50 );
				message_end ( );
			}
		}
	}

	set_task ( 5.0, "Draw_Medic_Repair_Sprites", TASK_DRAW_MEDIC_SPRITES );

	return PLUGIN_CONTINUE;

}
