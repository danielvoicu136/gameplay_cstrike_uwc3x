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
	log_amx ( "[UWC3X] SQLite :: Loading..." );
	new szError[256], iErrNum;

	// Set up the tuple that will be used for threading
	g_SqlTuple = SQL_MakeDbTuple( "", "", "", "uwc3x" );

	// Attempt to connect
	SqlConnection = SQL_Connect( g_SqlTuple, iErrNum, szError, 255 );

	if ( !SqlConnection )
	{
		log_amx ("[SQLITE] Database Connection Failed: [%d] %s", iErrNum, szError );

		return PLUGIN_CONTINUE;
	}

	server_print( "[UWC3X] SQLite database connection successful" );

	new Handle:query;
	format ( squery, 4096, "CREATE TABLE `uwc3x` ( `steamid` VARCHAR ( 32 ) NOT NULL, `xp` INT, `ip` " );
	format ( squery, 4096, "%s%s", squery, "VARCHAR ( 32 ), `mtime` VARCHAR ( 32 ), `skill1` SMALLINT DEFAULT '0', `skill2` SMALLINT " );
	format ( squery, 4096, "%s%s", squery, "DEFAULT '0', `skill3` SMALLINT DEFAULT '0', `skill4` SMALLINT DEFAULT '0', `skill5` " );
	format ( squery, 4096, "%s%s", squery, "SMALLINT DEFAULT '0', `skill6` SMALLINT DEFAULT '0', `skill7` SMALLINT DEFAULT '0', " );
	format ( squery, 4096, "%s%s", squery, "`skill8` SMALLINT DEFAULT '0', `skill9` SMALLINT DEFAULT '0', `skill10` SMALLINT " );
	format ( squery, 4096, "%s%s", squery, "DEFAULT '0', `skill11` SMALLINT DEFAULT '0', `skill12` SMALLINT DEFAULT '0', `skill13` " );
	format ( squery, 4096, "%s%s", squery, "SMALLINT DEFAULT '0', `skill14` SMALLINT DEFAULT '0', `skill15` SMALLINT DEFAULT '0', " ) ;
	format ( squery, 4096, "%s%s", squery, "`skill16` SMALLINT DEFAULT '0', `skill17` SMALLINT DEFAULT '0', `skill18` SMALLINT " );
	format ( squery, 4096, "%s%s", squery, "DEFAULT '0', `skill19` SMALLINT DEFAULT '0', `skill20` SMALLINT DEFAULT '0', `skill21` " );
	format ( squery, 4096, "%s%s", squery, "SMALLINT DEFAULT '0', `skill22` SMALLINT DEFAULT '0', `skill23` SMALLINT DEFAULT '0', " );
	format ( squery, 4096, "%s%s", squery, "`skill24` SMALLINT DEFAULT '0', `skill25` SMALLINT DEFAULT '0', `skill26` SMALLINT " ) ;
	format ( squery, 4096, "%s%s", squery, "DEFAULT '0' , `skill27` SMALLINT DEFAULT '0', `skill28` SMALLINT DEFAULT '0', " );
	format ( squery, 4096, "%s%s", squery, "`skill29` SMALLINT DEFAULT '0', `skill30` SMALLINT DEFAULT '0', `skill31` SMALLINT " );
	format ( squery, 4096, "%s%s", squery, "DEFAULT '0', `skill32` SMALLINT DEFAULT '0', `skill33` SMALLINT DEFAULT '0', " );
	format ( squery, 4096, "%s%s", squery, "`skill34` SMALLINT DEFAULT '0', `skill35` SMALLINT DEFAULT '0', `skill36` SMALLINT " );
	format ( squery, 4096, "%s%s", squery, "DEFAULT '0', `skill37` SMALLINT DEFAULT '0', `skill38` SMALLINT DEFAULT '0', " ) ;
	format ( squery, 4096, "%s%s", squery, "`skill39` SMALLINT DEFAULT '0', `skill40` SMALLINT DEFAULT '0', `att1` SMALLINT " );
	format ( squery, 4096, "%s%s", squery, "DEFAULT '0', `att2` SMALLINT DEFAULT '0', `att3` SMALLINT DEFAULT '0', `att4` SMALLINT " );
	format ( squery, 4096, "%s%s", squery, "DEFAULT '0', `att5` SMALLINT DEFAULT '0', `att6` SMALLINT DEFAULT '0', `res1` SMALLINT DEFAULT '0', `res2` SMALLINT " );
	format ( squery, 4096, "%s%s", squery, "DEFAULT '0', `res3` SMALLINT DEFAULT '0', `res4` SMALLINT DEFAULT '0', `res5` SMALLINT " );
	format ( squery, 4096, "%s%s", squery, "DEFAULT '0', PRIMARY KEY ( `steamid` ) )" );

	query = SQL_PrepareQuery( SqlConnection, squery );

	// run the query
	if ( !Query || !SQL_Execute ( Query ) )
	{
		// if there were any problems
		SQL_QueryError ( Query, g_Error, 511 );
		log_amx ( "UWC3X SQLite :: Error creating table" );
		log_amx ( "Error:: %s", g_Error );
		log_amx ( "Query:: %s", squery );
	}
	else
	{
		//Free the stuff
		SQL_FreeHandle ( Query );
		SQL_FreeHandle ( SqlConnection );
	}

	if( !sqlite_TableExists( SqlConnection, "uwc3x") )
	{
		if ( !SQL_Execute( query ) )
		{
			//SQLITE_Error( query, "uwc3x", 1 );
			return PLUGIN_CONTINUE;
		}
	}

	SQL_FreeHandle( query );
	return PLUGIN_CONTINUE;

}
public LoadSQLLiteVars ( )
{

}

public RunSQLLiteQuerry ( FailState, Handle:sQuery, sError[], sErrorCode, Data[], DataSize )
{

}
public CreateSQLLiteTable ( FailState, Handle:Query, Error[], Errcode, Data[], DataSize )
{


	return;
}

public _LoadXPSQLLite ( FailState, Handle:sQuery, sError[], sErrorCode, Data[], DataSize )
{

}
public LoadXPSQLLite ( id )
{

}

public _SaveXPSQLLite ( FailState, Handle:sQuery, sError[], sErrorCode, Data[], DataSize )
{

}

public SaveXPSQLLite ( id )
{

}
public SQLLiteClose ( )
{

}
public SaveSkillSetSQLLite ( id, skillsetIDX )
{

}
public LoadSkillSetSQLLite ( id, skillsetIDX )
{

}

public DeleteSkillSetSQLLite( id, skillsetIDX )
{

}

