
public IsSQLiteConnected ( )
{
	if( bDBConn )
	{
		return true;
	}

	return false;
}


public LoadSQLLiteConfig ( )
{
	//No configs to load for sqlite
	log_amx( "[UWC3X] SQLite :: Loading Config..." );
	LoadSQLLiteVars();
	return PLUGIN_CONTINUE;
}


public LoadSQLLiteVars ( )
{
	//Load the Cvars into locally used strings
	log_amx( "[UWC3X] SQLite :: Setting Vars..." );

	//Create handle and then the connection
	g_SqlTuple = SQL_MakeDbTuple ( "", "", "", CVAR_MYSQL_DATABASE );

	//Try and connect
	SqlConnection = SQL_Connect ( g_SqlTuple, ErrorCode, g_Error, 511 );

	//Check for an error
	if ( !SqlConnection )
	{
		log_amx( "[UWC3X] Error connecting to SQLite database : %s", g_Error );
		bDBConn = false;
		return PLUGIN_CONTINUE;
	}
	else
	{
		log_amx( "[UWC3X] SQLite :: Connected [OK]" );
		bDBConn = true;
	}

	format ( squery, 5096, "CREATE TABLE IF NOT EXISTS `%s` ( `steamid` VARCHAR ( 32 ) NOT NULL, `xp` INT, `ip` ", CVAR_MYSQL_TABLE );
	format ( squery, 5096, "%s%s", squery, "VARCHAR ( 32 ), `mtime` VARCHAR ( 32 ), `skill1` SMALLINT DEFAULT '0', `skill2` SMALLINT " );
	format ( squery, 5096, "%s%s", squery, "DEFAULT '0', `skill3` SMALLINT DEFAULT '0', `skill4` SMALLINT DEFAULT '0', `skill5` " );
	format ( squery, 5096, "%s%s", squery, "SMALLINT DEFAULT '0', `skill6` SMALLINT DEFAULT '0', `skill7` SMALLINT DEFAULT '0', " );
	format ( squery, 5096, "%s%s", squery, "`skill8` SMALLINT DEFAULT '0', `skill9` SMALLINT DEFAULT '0', `skill10` SMALLINT " );
	format ( squery, 5096, "%s%s", squery, "DEFAULT '0', `skill11` SMALLINT DEFAULT '0', `skill12` SMALLINT DEFAULT '0', `skill13` " );
	format ( squery, 5096, "%s%s", squery, "SMALLINT DEFAULT '0', `skill14` SMALLINT DEFAULT '0', `skill15` SMALLINT DEFAULT '0', " ) ;
	format ( squery, 5096, "%s%s", squery, "`skill16` SMALLINT DEFAULT '0', `skill17` SMALLINT DEFAULT '0', `skill18` SMALLINT " );
	format ( squery, 5096, "%s%s", squery, "DEFAULT '0', `skill19` SMALLINT DEFAULT '0', `skill20` SMALLINT DEFAULT '0', `skill21` " );
	format ( squery, 5096, "%s%s", squery, "SMALLINT DEFAULT '0', `skill22` SMALLINT DEFAULT '0', `skill23` SMALLINT DEFAULT '0', " );
	format ( squery, 5096, "%s%s", squery, "`skill24` SMALLINT DEFAULT '0', `skill25` SMALLINT DEFAULT '0', `skill26` SMALLINT " ) ;
	format ( squery, 5096, "%s%s", squery, "DEFAULT '0' , `skill27` SMALLINT DEFAULT '0', `skill28` SMALLINT DEFAULT '0', " );
	format ( squery, 5096, "%s%s", squery, "`skill29` SMALLINT DEFAULT '0', `skill30` SMALLINT DEFAULT '0', `skill31` SMALLINT " );
	format ( squery, 5096, "%s%s", squery, "DEFAULT '0', `skill32` SMALLINT DEFAULT '0', `skill33` SMALLINT DEFAULT '0', " );
	format ( squery, 5096, "%s%s", squery, "`skill34` SMALLINT DEFAULT '0', `skill35` SMALLINT DEFAULT '0', `skill36` SMALLINT " );
	format ( squery, 5096, "%s%s", squery, "DEFAULT '0', `skill37` SMALLINT DEFAULT '0', `skill38` SMALLINT DEFAULT '0', " ) ;
	format ( squery, 5096, "%s%s", squery, "`skill39` SMALLINT DEFAULT '0', `skill40` SMALLINT DEFAULT '0', `skill41` SMALLINT DEFAULT '0', " );
	format ( squery, 5096, "%s%s", squery, "`skill42` SMALLINT DEFAULT '0', `skill43` SMALLINT DEFAULT '0', `skill44` SMALLINT DEFAULT '0', " );
	format ( squery, 5096, "%s%s", squery, "`skill45` SMALLINT DEFAULT '0', `skill46` SMALLINT DEFAULT '0', `skill47` SMALLINT DEFAULT '0', " );
	format ( squery, 5096, "%s%s", squery, "`skill48` SMALLINT DEFAULT '0', `skill49` SMALLINT DEFAULT '0', `skill50` SMALLINT DEFAULT '0', " );
	format ( squery, 5096, "%s%s", squery, "`skill51` SMALLINT DEFAULT '0', `skill52` SMALLINT DEFAULT '0', `skill53` SMALLINT DEFAULT '0', " );
	format ( squery, 5096, "%s%s", squery, "`skill54` SMALLINT DEFAULT '0', `skill55` SMALLINT DEFAULT '0', `skill56` SMALLINT DEFAULT '0', " );
	format ( squery, 5096, "%s%s", squery, "`skill57` SMALLINT DEFAULT '0', `skill58` SMALLINT DEFAULT '0', `skill59` SMALLINT DEFAULT '0', " );
	format ( squery, 5096, "%s%s", squery, "`skill60` SMALLINT DEFAULT '0', `skill61` SMALLINT DEFAULT '0', `skill62` SMALLINT DEFAULT '0', " );
	format ( squery, 5096, "%s%s", squery, "`skill63` SMALLINT DEFAULT '0', `skill64` SMALLINT DEFAULT '0', " );
	format ( squery, 5096, "%s%s", squery, "`att1` SMALLINT DEFAULT '0', `att2` SMALLINT DEFAULT '0', `att3` SMALLINT DEFAULT '0', `att4` SMALLINT " );
	format ( squery, 5096, "%s%s", squery, "DEFAULT '0', `att5` SMALLINT DEFAULT '0', `att6` SMALLINT DEFAULT '0', `res1` SMALLINT DEFAULT '0', `res2` SMALLINT " );
	format ( squery, 5096, "%s%s", squery, "DEFAULT '0', `res3` SMALLINT DEFAULT '0', `res4` SMALLINT DEFAULT '0', `res5` SMALLINT DEFAULT '0', `res6` SMALLINT DEFAULT '0', `res7` SMALLINT " );

	//If save by = 2 (by name) primary key is the name
	if( CVAR_SAVE_BY == 2 )
	{
		format ( squery, 5096, "%s%s", squery, "DEFAULT '0', `name` VARCHAR ( 64 ) DEFAULT NULL, PRIMARY KEY ( `name` ));" );
	}
	else
	{
		format ( squery, 5096, "%s%s", squery, "DEFAULT '0', `name` VARCHAR ( 64 ) DEFAULT NULL, PRIMARY KEY ( `steamid`));" );
	}

	//Set the Query
	Query = SQL_PrepareQuery ( SqlConnection, squery );

	// run the query
	if ( !Query || !SQL_Execute ( Query ) )
	{
		// if there were any problems
		SQL_QueryError ( Query, g_Error, 511 );
		log_amx( "[UWC3X] SQLLite :: Error creating table" );
		log_amx( "[UWC3X] Error:: %s", g_Error );
		log_amx( "[UWC3X] Query:: %s", squery );
	}
	else
	{
		//Free the stuff
		SQL_FreeHandle ( Query );
		SQL_FreeHandle ( SqlConnection );
	}

	return PLUGIN_CONTINUE;
}

public SkillSetsSqlLite_Table ( )
{
	if( CVAR_SAVED_SKILLSETS )
	{
		log_amx( "[UWC3X] SQLite :: Using Saved Skill Sets [OK]" );
		//Create handle and then the connection
		g_SqlTuple = SQL_MakeDbTuple ( CVAR_MYSQL_HOSTNAME, CVAR_MYSQL_USERNAME, CVAR_MYSQL_PASSWORD, CVAR_MYSQL_DATABASE );

		//Try and connect
		SqlConnection = SQL_Connect ( g_SqlTuple, ErrorCode, g_Error, 511 );

		//Check for an error
		if ( !SqlConnection )
		{
			log_amx( "[UWC3X] SQLite :: Created Skill Sets Table [FAILED]" );
			log_amx( "[UWC3X] Error connecting to SQLite database : %s", g_Error );
			bDBConn = false;
			return PLUGIN_CONTINUE;
		}

		log_amx( "[UWC3X] SQLite :: Connected [OK]" );

		if( CVAR_SAVE_BY == 2 )
		{
			format ( squery, 5096, "CREATE TABLE IF NOT EXISTS `%s_SkillSets` ( `name` VARCHAR(64), `skillsetid` INTEGER , ", CVAR_MYSQL_TABLE );
		}
		else
		{
			format ( squery, 5096, "CREATE TABLE IF NOT EXISTS `%s_SkillSets` ( `steamid` VARCHAR(32), `skillsetid` INTEGER , ", CVAR_MYSQL_TABLE );
		} 

		format ( squery, 5096, "%s%s", squery, "`skill1` SMALLINT DEFAULT '0', `skill2` SMALLINT DEFAULT '0', `skill3` SMALLINT DEFAULT '0', " );
		format ( squery, 5096, "%s%s", squery, "`skill4` SMALLINT DEFAULT '0', `skill5` SMALLINT DEFAULT '0', `skill6` SMALLINT DEFAULT '0', " );
		format ( squery, 5096, "%s%s", squery, "`skill7` SMALLINT DEFAULT '0', `skill8` SMALLINT DEFAULT '0', `skill9` SMALLINT DEFAULT '0', " );
		format ( squery, 5096, "%s%s", squery, "`skill10` SMALLINT DEFAULT '0', `skill11` SMALLINT DEFAULT '0', `skill12` SMALLINT DEFAULT '0', " );
		format ( squery, 5096, "%s%s", squery, "`skill13` SMALLINT DEFAULT '0', `skill14` SMALLINT DEFAULT '0', `skill15` SMALLINT DEFAULT '0', " );
		format ( squery, 5096, "%s%s", squery, "`skill16` SMALLINT DEFAULT '0', `skill17` SMALLINT DEFAULT '0', `skill18` SMALLINT DEFAULT '0', " );
		format ( squery, 5096, "%s%s", squery, "`skill19` SMALLINT DEFAULT '0', `skill20` SMALLINT DEFAULT '0', `skill21` SMALLINT DEFAULT '0', " );
		format ( squery, 5096, "%s%s", squery, "`skill22` SMALLINT DEFAULT '0', `skill23` SMALLINT DEFAULT '0', `skill24` SMALLINT DEFAULT '0', " );
		format ( squery, 5096, "%s%s", squery, "`skill25` SMALLINT DEFAULT '0', `skill26` SMALLINT DEFAULT '0', `skill27` SMALLINT DEFAULT '0', " );
		format ( squery, 5096, "%s%s", squery, "`skill28` SMALLINT DEFAULT '0', `skill29` SMALLINT DEFAULT '0', `skill30` SMALLINT DEFAULT '0', " );
		format ( squery, 5096, "%s%s", squery, "`skill31` SMALLINT DEFAULT '0', `skill32` SMALLINT DEFAULT '0', `skill33` SMALLINT DEFAULT '0', " );
		format ( squery, 5096, "%s%s", squery, "`skill34` SMALLINT DEFAULT '0', `skill35` SMALLINT DEFAULT '0', `skill36` SMALLINT DEFAULT '0', " );
		format ( squery, 5096, "%s%s", squery, "`skill37` SMALLINT DEFAULT '0', `skill38` SMALLINT DEFAULT '0', `skill39` SMALLINT DEFAULT '0', " );
		format ( squery, 5096, "%s%s", squery, "`skill40` SMALLINT DEFAULT '0', `skill41` SMALLINT DEFAULT '0', `skill42` SMALLINT DEFAULT '0', " );
		format ( squery, 5096, "%s%s", squery, "`skill43` SMALLINT DEFAULT '0', `skill44` SMALLINT DEFAULT '0', `skill45` SMALLINT DEFAULT '0', " );
		format ( squery, 5096, "%s%s", squery, "`skill46` SMALLINT DEFAULT '0', `skill47` SMALLINT DEFAULT '0', `skill48` SMALLINT DEFAULT '0', " );
		format ( squery, 5096, "%s%s", squery, "`skill49` SMALLINT DEFAULT '0', `skill50` SMALLINT DEFAULT '0', `skill51` SMALLINT DEFAULT '0', " );
		format ( squery, 5096, "%s%s", squery, "`skill52` SMALLINT DEFAULT '0', `skill53` SMALLINT DEFAULT '0', `skill54` SMALLINT DEFAULT '0', " );
		format ( squery, 5096, "%s%s", squery, "`skill55` SMALLINT DEFAULT '0', `skill56` SMALLINT DEFAULT '0', `skill57` SMALLINT DEFAULT '0', " );
		format ( squery, 5096, "%s%s", squery, "`skill58` SMALLINT DEFAULT '0', `skill59` SMALLINT DEFAULT '0', `skill60` SMALLINT DEFAULT '0', " );
		format ( squery, 5096, "%s%s", squery, "`skill61` SMALLINT DEFAULT '0', `skill62` SMALLINT DEFAULT '0', `skill63` SMALLINT DEFAULT '0', " );
		format ( squery, 5096, "%s%s", squery, "`skill64` SMALLINT DEFAULT '0' );" );

		//Set the Query
		Query = SQL_PrepareQuery ( SqlConnection, squery );

		// run the query
		if ( !Query || !SQL_Execute ( Query ) )
		{
			// if there were any problems
			SQL_QueryError ( Query, g_Error, 511 );
			log_amx( "[UWC3X] SQLite :: Error creating table" );
			log_amx( "[UWC3X] Error:: %s", g_Error );
			log_amx( "[UWC3X] Query:: %s", squery );
		}
		else
		{
			//Free the stuff
			SQL_FreeHandle ( Query );
			SQL_FreeHandle ( SqlConnection );
		}

		log_amx( "[UWC3X] SQLite :: Created Skill Sets Table [OK]" );
		return PLUGIN_CONTINUE;
	}
	else
	{
		log_amx( "[UWC3X] SQLite :: Using Saved Skill Sets [NO]" );
		return PLUGIN_CONTINUE;
	}

	return PLUGIN_CONTINUE;
}


public LoadXPSQLLite ( id )
{

	if ( CVAR_ENABLE_UWC3X != 1 )
	{
		return PLUGIN_HANDLED;
	}

	if ( CVAR_SAVE_XP != 1 )
	{
		return PLUGIN_CONTINUE;
	}

	new tempVar[64], tempVar2[64];
	if( CVAR_SAVE_BY == 2 )
	{
		copy( tempVar, 32, "name");
		get_user_name ( id, tempVar2, 63 );

		remove_quotes(tempVar2);
		while(replace(tempVar2,63,"'","")) { }
		while(replace(tempVar2,63,")","")) { }
		while(replace(tempVar2,63,"(","")) { }
		while(replace(tempVar2,63,";","")) { }
	}
	else
	{
		copy( tempVar, 32, "steamid");
		get_user_authid ( id, tempVar2, 63 );
	}

	format ( squery, 4096, "SELECT steamid, xp, ip, mtime, skill1, skill2, skill3," );
	format ( squery, 4096, "%s skill4, skill5, skill6, skill7, skill8, skill9, skill10, ", squery );
	format ( squery, 4096, "%s skill11, skill12, skill13, skill14, skill15, skill16, skill17,", squery );
	format ( squery, 4096, "%s skill18, skill19, skill20, skill21, skill22, skill23, skill24,", squery );
	format ( squery, 4096, "%s skill25, skill26, skill27, skill28, skill29, skill30, skill31,", squery );
	format ( squery, 4096, "%s skill32, skill33, skill34, skill35, skill36, skill37, skill38,", squery );
	format ( squery, 4096, "%s skill39, skill40, skill41, skill42, skill43, skill44, skill45,", squery );
	format ( squery, 4096, "%s skill46, skill47, skill48, skill49, skill50, skill51, skill52,", squery );
	format ( squery, 4096, "%s skill53, skill54, skill55, skill56, skill57, skill58, skill59,", squery );
	format ( squery, 4096, "%s skill60, skill61, skill62, skill63, skill64,", squery );
	format ( squery, 4096, "%s att1, att2, att3, att4, att5, att6, res1, res2,", squery );
	format ( squery, 4096, "%s res3, res4, res5, res6, res7, name FROM %s WHERE %s = '%s';", squery, CVAR_MYSQL_TABLE, tempVar, tempVar2 );

	player_id = id;

	//Set the Query
	Query = SQL_PrepareQuery ( SqlConnection, squery );

	// run the query
	if ( !Query || !SQL_Execute ( Query ) )
	{
		// if there were any problems
		SQL_QueryError ( Query, g_Error, 511 );
		log_amx( "[UWC3X] SQLLite :: Error Getting player XP" );
		log_amx( "[UWC3X] Error:: %s", g_Error );
		log_amx( "[UWC3X] Query:: %s", squery );
	}
	else
	{
		//Free the stuff
		SQL_FreeHandle ( Query );
		SQL_FreeHandle ( SqlConnection );
	}

	return PLUGIN_CONTINUE;

}

public SaveXPSQLLite ( id )
{
	if ( CVAR_ENABLE_UWC3X != 1 )
	{
		return PLUGIN_HANDLED;
	}

	if ( CVAR_SAVE_XP != 1 )
	{
		return PLUGIN_CONTINUE;
	}
	
	new tempVar[64];
	get_user_name ( id, tempVar, 63 );
	get_user_authid ( id, steamid, 34 );
	remove_quotes(tempVar);

	while(replace(tempVar,63,"'","")) { }
	while(replace(tempVar,63,")","")) { }
	while(replace(tempVar,63,"(","")) { }
	while(replace(tempVar,63,";","")) { }

	if ( CVAR_ENABLE_STARTING_SYSTEM )
	{
		if( CVAR_STARTING_METHOD == 1 )
		{
			if ( playerxp[id] <= CVAR_STARTING_XP )
			{
				playerxp[id] = CVAR_STARTING_XP;
			}
		}
		else
		{
			if( is_user_bot( id ))
			{			
				if ( playerxp[id] <= xplevel_lev[CVAR_BOT_LEVEL] )
				{
					playerxp[id] = xplevel_lev[CVAR_BOT_LEVEL];
				}			
			}
			else
			{
				//If they are a bot, then dont save, always use the bot level insetead to set XP
				if( is_user_bot( id ))
				{
					playerxp[id] = xplevel_lev[CVAR_BOT_LEVEL];
					if( CVAR_DEBUG_MODE )
					{
						log_amx( "[UWC3X] DEBUG :: SQLLite SaveXPSQLLite -> is_user_bot1 name %s auth %s xp %d", tempVar, steamid, playerxp[id] );
					}
				}
				else
				{
					if ( playerxp[id] <= xplevel_lev[CVAR_STARTING_LEVEL] )
					{
						playerxp[id] = xplevel_lev[CVAR_STARTING_LEVEL];
					}
				}
			}
		}
	}

	get_time ( "%d/%m/%Y %H:%M:%S", mtimet, 31 );
	format ( squery, 4096, "REPLACE INTO `%s` SET steamid='%s', xp='%d',", CVAR_MYSQL_TABLE, steamid, playerxp[id] );
	format ( squery, 4096, "%s mtime='%s' , skill1='%d' , skill2='%d' ,", squery, mtimet, p_skills[id][1], p_skills[id][2] ) ;
	format ( squery, 4096, "%s skill3='%d' , skill4='%d' , skill5='%d' ,", squery,p_skills[id][3], p_skills[id][4], p_skills[id][5] );
	format ( squery, 4096, "%s skill6='%d' , skill7='%d' , skill8='%d' ,", squery,p_skills[id][6], p_skills[id][7], p_skills[id][8] );
	format ( squery, 4096, "%s skill9='%d' , skill10='%d', skill11='%d',", squery,p_skills[id][9], p_skills[id][10], p_skills[id][11] );
	format ( squery, 4096, "%s skill12='%d', skill13='%d', skill14='%d',", squery,p_skills[id][12], p_skills[id][13], p_skills[id][14] );
	format ( squery, 4096, "%s skill15='%d', skill16='%d', skill17='%d',", squery,p_skills[id][15], p_skills[id][16], p_skills[id][17] ) ;
	format ( squery, 4096, "%s skill18='%d', skill19='%d', skill20='%d',", squery,p_skills[id][18], p_skills[id][19], p_skills[id][20] );
	format ( squery, 4096, "%s skill21='%d', skill22='%d', skill23='%d',", squery,p_skills[id][21], p_skills[id][22], p_skills[id][23] );
	format ( squery, 4096, "%s skill24='%d', skill25='%d', skill26='%d',", squery,p_skills[id][24], p_skills[id][25], p_skills[id][26] );
	format ( squery, 4096, "%s skill27='%d', skill28='%d', skill29='%d',", squery,p_skills[id][27], p_skills[id][28], p_skills[id][29] );
	format ( squery, 4096, "%s skill30='%d', skill31='%d', skill32='%d',", squery,p_skills[id][30], p_skills[id][31], p_skills[id][32] );
	format ( squery, 4096, "%s skill33='%d', skill34='%d', skill35='%d',", squery,p_skills[id][33], p_skills[id][34], p_skills[id][35] );
	format ( squery, 4096, "%s skill36='%d', skill37='%d', skill38='%d',", squery,p_skills[id][36], p_skills[id][37], p_skills[id][38] );
	format ( squery, 4096, "%s skill39='%d', skill40='%d', skill41='%d',", squery,p_skills[id][39], p_skills[id][40], p_skills[id][41] );
	format ( squery, 4096, "%s skill42='%d', skill43='%d', skill44='%d',", squery,p_skills[id][42], p_skills[id][43], p_skills[id][44] );
	format ( squery, 4096, "%s skill45='%d', skill46='%d', skill47='%d',", squery,p_skills[id][45], p_skills[id][46], p_skills[id][47] );
	format ( squery, 4096, "%s skill48='%d', skill49='%d', skill50='%d',", squery,p_skills[id][48], p_skills[id][49], p_skills[id][50] );
	format ( squery, 4096, "%s skill51='%d', skill52='%d', skill53='%d',", squery,p_skills[id][51], p_skills[id][52], p_skills[id][53] );
	format ( squery, 4096, "%s skill54='%d', skill55='%d', skill56='%d',", squery, p_skills[id][54],p_skills[id][55], p_skills[id][56] );
	format ( squery, 4096, "%s skill57='%d', skill58='%d', skill59='%d',", squery,p_skills[id][57], p_skills[id][58], p_skills[id][59] );
	format ( squery, 4096, "%s skill60='%d', skill61='%d', skill62='%d',", squery,p_skills[id][60], p_skills[id][61], p_skills[id][62] );
	format ( squery, 4096, "%s skill63='%d', skill64='%d', ", squery, p_skills[id][63],p_skills[id][64] );
	format ( squery, 4096, "%s att1='%d' , att2='%d' , att3='%d' , att4='%d' ,", squery, p_attribs[id][ATTRIBIDX_STR], p_attribs[id][ATTRIBIDX_INT], p_attribs[id][ATTRIBIDX_DEX], p_attribs[id][ATTRIBIDX_AGI] );
	format ( squery, 4096, "%s att5='%d' , att6='%d' , res1='%d' , res2='%d' ,", squery, p_attribs[id][ATTRIBIDX_CON], p_attribs[id][ATTRIBIDX_WIS], p_resists[id][RESISTIDX_POISON], p_resists[id][RESISTIDX_DISEASE] );
	format ( squery, 4096, "%s res3='%d' , res4='%d' , res5='%d' , res6='%d', res7='%d', name='%s' ;", squery, p_resists[id][RESISTIDX_ELECTRIC], p_resists[id][RESISTIDX_FIRE], p_resists[id][RESISTIDX_MAGIC], p_resists[id][RESISTIDX_ROT],p_resists[id][RESISTIDX_ICE], tempVar );

	player_id = id;

	//Set the Query
	Query = SQL_PrepareQuery ( SqlConnection, squery );

	// run the query
	if ( !Query || !SQL_Execute ( Query ) )
	{
		// if there were any problems
		SQL_QueryError ( Query, g_Error, 511 );
		log_amx( "[UWC3X] SQLLite :: Error Saving player XP" );
		log_amx( "[UWC3X] Error:: %s", g_Error );
		log_amx( "[UWC3X] Query:: %s", squery );
	}
	else
	{
		//Free the stuff
		SQL_FreeHandle ( Query );
		SQL_FreeHandle ( SqlConnection );
	}


	return PLUGIN_CONTINUE;
}




public DeleteSkillSetSQLLite ( id, skillsetIDX )
{
	if ( CVAR_ENABLE_UWC3X != 1 )
	{
		return PLUGIN_HANDLED;
	}

	if ( CVAR_SAVE_XP != 1 )
	{
		return PLUGIN_CONTINUE;
	}

	if( CVAR_SAVE_BY == 2 )
	{
		new userName[63];
		get_user_name ( id, userName, 63 );
		format ( squery, 4096, "Delete from `%s_SkillSets` where name='%s' and skillsetid='%d',", CVAR_MYSQL_TABLE, userName, skillsetIDX );
	}
	else
	{
		get_user_authid ( id, steamid, 34 );
		format ( squery, 4096, "Delete from `%s_SkillSets` where steamid='%s' and skillsetid='%d',", CVAR_MYSQL_TABLE, steamid, skillsetIDX );
	}

	player_id = id;
	skills_id = skillsetIDX;
	if ( CVAR_DEBUG_MODE )
	{
		log_amx( "[UWC3X] DEBUG: SQLIte->DeleteSkillSetSQLLite" );
	}

	//Set the Query
	Query = SQL_PrepareQuery ( SqlConnection, squery );

	// run the query
	if ( !Query || !SQL_Execute ( Query ) )
	{
		// if there were any problems
		SQL_QueryError ( Query, g_Error, 511 );
		log_amx( "[UWC3X] SQLLite :: Error Deleting player skill set" );
		log_amx( "[UWC3X] Error:: %s", g_Error );
		log_amx( "[UWC3X] Query:: %s", squery );
	}
	else
	{
		//Free the stuff
		SQL_FreeHandle ( Query );
		SQL_FreeHandle ( SqlConnection );
	}

	return PLUGIN_CONTINUE;

}
public SaveSkillSetSQLLite( id, skillsetIDX )
{

	if ( CVAR_ENABLE_UWC3X != 1 )
	{
		return PLUGIN_HANDLED;
	}

	if ( CVAR_SAVE_XP != 1 )
	{
		return PLUGIN_CONTINUE;
	}

	if( CVAR_SAVE_BY == 2 )
	{
		new userName[63];
		get_user_name ( id, userName, 63 );
		format ( squery, 5096, "REPLACE INTO `%s_SkillSets` SET name='%s', skillsetid='%d',", CVAR_MYSQL_TABLE, userName, skillsetIDX );
	}
	else
	{
		get_user_authid ( id, steamid, 34 );
		format ( squery, 5096, "REPLACE INTO `%s_SkillSets` SET steamid='%s', skillsetid='%d',", CVAR_MYSQL_TABLE, steamid, skillsetIDX );
	}
	
	format ( squery, 4096, "%s skill1='%d' , skill2='%d' ,", squery, p_skills[id][1], p_skills[id][2] ) ;
	format ( squery, 4096, "%s skill3='%d' , skill4='%d' , skill5='%d' ,", squery,p_skills[id][3], p_skills[id][4], p_skills[id][5] );
	format ( squery, 4096, "%s skill6='%d' , skill7='%d' , skill8='%d' ,", squery,p_skills[id][6], p_skills[id][7], p_skills[id][8] );
	format ( squery, 4096, "%s skill9='%d' , skill10='%d', skill11='%d',", squery,p_skills[id][9], p_skills[id][10], p_skills[id][11] );
	format ( squery, 4096, "%s skill12='%d', skill13='%d', skill14='%d',", squery,p_skills[id][12], p_skills[id][13], p_skills[id][14] );
	format ( squery, 4096, "%s skill15='%d', skill16='%d', skill17='%d',", squery,p_skills[id][15], p_skills[id][16], p_skills[id][17] ) ;
	format ( squery, 4096, "%s skill18='%d', skill19='%d', skill20='%d',", squery,p_skills[id][18], p_skills[id][19], p_skills[id][20] );
	format ( squery, 4096, "%s skill21='%d', skill22='%d', skill23='%d',", squery,p_skills[id][21], p_skills[id][22], p_skills[id][23] );
	format ( squery, 4096, "%s skill24='%d', skill25='%d', skill26='%d',", squery,p_skills[id][24], p_skills[id][25], p_skills[id][26] );
	format ( squery, 4096, "%s skill27='%d', skill28='%d', skill29='%d',", squery,p_skills[id][27], p_skills[id][28], p_skills[id][29] );
	format ( squery, 4096, "%s skill30='%d', skill31='%d', skill32='%d',", squery,p_skills[id][30], p_skills[id][31], p_skills[id][32] );
	format ( squery, 4096, "%s skill33='%d', skill34='%d', skill35='%d',", squery,p_skills[id][33], p_skills[id][34], p_skills[id][35] );
	format ( squery, 4096, "%s skill36='%d', skill37='%d', skill38='%d',", squery,p_skills[id][36], p_skills[id][37], p_skills[id][38] );
	format ( squery, 4096, "%s skill39='%d', skill40='%d', skill41='%d',", squery,p_skills[id][39], p_skills[id][40], p_skills[id][41] );
	format ( squery, 4096, "%s skill42='%d', skill43='%d', skill44='%d',", squery,p_skills[id][42], p_skills[id][43], p_skills[id][44] );
	format ( squery, 4096, "%s skill45='%d', skill46='%d', skill47='%d',", squery,p_skills[id][45], p_skills[id][46], p_skills[id][47] );
	format ( squery, 4096, "%s skill48='%d', skill49='%d', skill50='%d',", squery,p_skills[id][48], p_skills[id][49], p_skills[id][50] );
	format ( squery, 4096, "%s skill51='%d', skill52='%d', skill53='%d',", squery,p_skills[id][51], p_skills[id][52], p_skills[id][53] );
	format ( squery, 4096, "%s skill54='%d', skill55='%d', skill56='%d',", squery, p_skills[id][54],p_skills[id][55], p_skills[id][56] );
	format ( squery, 4096, "%s skill57='%d', skill58='%d', skill59='%d',", squery,p_skills[id][57], p_skills[id][58], p_skills[id][59] );
	format ( squery, 4096, "%s skill60='%d', skill61='%d', skill62='%d',", squery,p_skills[id][60], p_skills[id][61], p_skills[id][62] );
	format ( squery, 4096, "%s skill63='%d', skill64='%d' ;", squery, p_skills[id][63],p_skills[id][64] );

	player_id = id;
	skills_id = skillsetIDX;
	if ( CVAR_DEBUG_MODE )
	{
		log_amx( "[UWC3X] DEBUG: SQLLite->SaveSkillSetSQLLite: Set SQL_ThreadQuery" );
	}

	//Set the Query
	Query = SQL_PrepareQuery ( SqlConnection, squery );

	// run the query
	if ( !Query || !SQL_Execute ( Query ) )
	{
		// if there were any problems
		SQL_QueryError ( Query, g_Error, 511 );
		log_amx( "[UWC3X] SQLLite :: Error Saving player skill set" );
		log_amx( "[UWC3X] Error:: %s", g_Error );
		log_amx( "[UWC3X] Query:: %s", squery );
	}
	else
	{
		//Free the stuff
		SQL_FreeHandle ( Query );
		SQL_FreeHandle ( SqlConnection );
	}

	return PLUGIN_CONTINUE;

}

public LoadSkillSetSQLLite( id, skillsetIDX )
{

	if ( CVAR_ENABLE_UWC3X != 1 )
	{
		return PLUGIN_HANDLED;
	}

	if ( CVAR_SAVE_XP != 1 )
	{
		return PLUGIN_CONTINUE;
	}

	if( CVAR_SAVE_BY == 2 )
	{
		format ( squery, 4096, "SELECT name, skill1, skill2, skill3," );
	}
	else
	{
		format ( squery, 4096, "SELECT steamid, skill1, skill2, skill3," );
	}

	format ( squery, 4096, "%s skill4, skill5, skill6, skill7, skill8, skill9, skill10, ", squery );
	format ( squery, 4096, "%s skill11, skill12, skill13, skill14, skill15, skill16, skill17,", squery );
	format ( squery, 4096, "%s skill18, skill19, skill20, skill21, skill22, skill23, skill24,", squery );
	format ( squery, 4096, "%s skill25, skill26, skill27, skill28, skill29, skill30, skill31,", squery );
	format ( squery, 4096, "%s skill32, skill33, skill34, skill35, skill36, skill37, skill38,", squery );
	format ( squery, 4096, "%s skill39, skill40, skill41, skill42, skill43, skill44, skill45,", squery );
	format ( squery, 4096, "%s skill46, skill47, skill48, skill49, skill50, skill51, skill52,", squery );
	format ( squery, 4096, "%s skill53, skill54, skill55, skill56, skill57, skill58, skill59,", squery );
	format ( squery, 4096, "%s skill60, skill61, skill62, skill63, skill64 ", squery );

	if( CVAR_SAVE_BY == 2 )
	{
		new userName[63];
		get_user_name ( id, userName, 63 );
		format ( squery, 4096, "%s FROM %s_SkillSets WHERE name = '%s' and skillsetid = '%d';", squery, CVAR_MYSQL_TABLE, userName, skillsetIDX );
	}
	else
	{
		get_user_authid ( id, steamid, 34 );
		format ( squery, 4096, "%s FROM %s_SkillSets WHERE steamid = '%s' and skillsetid = '%d';", squery, CVAR_MYSQL_TABLE, steamid, skillsetIDX );
	}
	
	player_id = id;
	skills_id = skillsetIDX;
	if ( CVAR_DEBUG_MODE )
	{
		log_amx( "[UWC3X] DEBUG: SQLLite->LoadSkillSetSQLLite: Set SQL_ThreadQuery" );
	}

	SQL_ThreadQuery ( g_SqlTuple, "_LoadSkillSet", squery );
	return PLUGIN_CONTINUE;
}

public SQLLiteClose ( )
{
	if ( g_SqlTuple )
	{
		SQL_FreeHandle( g_SqlTuple );
	}

	if ( SqlConnection )
	{
		SQL_FreeHandle( SqlConnection );
	}
}


