/*
	menus
*/

public Initialize_Menus ( )
{
	// Menu related entries follow
	//register_menucmd ( register_menuid ( "\yUWC3X: Main Menu" ), 1023, "uwc3x_menu" ); 
	register_menucmd ( register_menuid ( "\ySelect an Attribute" ), 1023, "Attrib_Menu" );
	register_menucmd ( register_menuid ( "\ySelect a Resistance" ), 1023, "Resist_Menu" );
	register_menucmd ( register_menuid ( "\yHelp Menu" ), 1023, "help_menu" );
	//register_menucmd ( register_menuid ( "\yAdmin Menu" ), 1023, "do_adminmenu" );
	register_menucmd ( register_menuid ( "\ySkills Options" ), 1023, "do_skillsmenu" );
	register_menucmd ( register_menuid ( "\yItem Options" ), 1023, "Choose_Items_Menu" );
	//register_menucmd ( register_menuid ( "\yGive Players XP" ), 1023,"do_playerxpmenu" );
	//register_menucmd ( register_menuid ( "\yTeam XP Menu" ), 1023, "do_teamxpmenu" );
	register_menucmd ( register_menuid ( "Select Skill: " ), ( 1<<0 )| ( 1<<1 )| ( 1<<2 )| ( 1<<3 )| ( 1<<4 )| ( 1<<5 )| ( 1<<6 )| ( 1<<7 )| ( 1<<8 )| ( 1<<9 ), "set_skill" );
	register_menucmd ( register_menuid ( "Drop Skill: " ), ( 1<<0 )| ( 1<<1 )| ( 1<<2 )| ( 1<<3 )| ( 1<<4 )| ( 1<<5 )| ( 1<<6 )| ( 1<<7 )| ( 1<<8 )| ( 1<<9 ), "unset_skill" );
	register_menucmd ( register_menuid ( "\yBuy a Protection" ), 1023, "Buy_Item3" );
	register_menucmd ( register_menuid ( "\yBuy An Item" ), 1023, "Buy_Item2" );
	register_menucmd ( register_menuid ( "\yBuy Item" ), 1023, "Buy_Item" );
	//register_menucmd ( register_menuid ( "BuyItem" ), ( 1<<2 ),"Buy_Flash" );
	//register_menucmd ( register_menuid ( "BuyItem" ), ( 1<<3 ),"Buy_HE" );
	//register_menucmd ( -34, ( 1<<2 ), "Buy_Flash" );
	//register_menucmd ( -34, ( 1<<3 ), "Buy_HE" ); 

}

public Menu_Teleport ( parm[2] )
{
	new id = parm[0];
	new numberofplayers = parm[1];
	new targetid, origin[3], name[32], targetorigin[3], distancebetween, i, temp[64];
	new keys = ( 1<<9 );
	new menu_body[512];

	format ( menu_body,511,"\yTeleport To:\w^n" );
	get_user_origin ( id, origin );

	for ( i = 0; i < numberofplayers; ++i )
	{
		targetid = teleportid[id][i];
		get_user_name ( targetid, name, 31 );
		get_user_origin ( targetid, targetorigin );
		distancebetween = get_distance ( origin, targetorigin );

		if ( is_user_alive ( targetid ) )
		{
			format ( temp, 63, "^n\w%d. %s ( \y%dm\w )", i+1, name, distancebetween/40 );
			keys |= ( 1<<i );
		}
		else
		{
			format ( temp,63, "^n\d%d. %s", i+1, name );
		}

		add ( menu_body, 255, temp );

	}

	format ( temp,63,"^n^n\w0. %L", "CANCEL" );
	add ( menu_body, 255, temp );
	show_menu ( id, keys, menu_body, -1 );

	new menuparm[2];
	menuparm[0] = id;
	menuparm[1] = numberofplayers;

	if ( teleportmenu[id] )
	{
		set_task ( 1.0, "Menu_Teleport", TASK_MENU_TELEPORT + id, parm, 2 );
	}

	return PLUGIN_HANDLED;

}

public Menu_Skills( id )
{
	new pos = 0, i, menu_body[1024], menu_items[8][32];
	new keys = (1<<0)|(1<<1)|(1<<2)|(1<<3)|(1<<4)|(1<<5)|(1<<6)|(1<<7)|(1<<8)|(1<<9);

	menu_items[0]= "1st Tier Skills Information";
	menu_items[1]= "2nd Tier Skills Information";
	menu_items[2]= "3rd Tier Skills Information";
	menu_items[3]= "4th Tier Skills Information";
	menu_items[4]= "5th Tier Skills Information";
	menu_items[5]= "6th Tier Skills Information";
	menu_items[6]= "7th Tier Skills Information";
	menu_items[7]= "8th Tier Skills Information";

	pos += format(menu_body[pos], 1024-pos, "\ySkills Options^n^n");
	for (i = 0; i < MAX_SKILL_PAGES; i++)
	{
		pos += format(menu_body[pos], 1024-pos, "\w%d. %s^n",i+1,menu_items[i]);
	}
	pos += format(menu_body[pos], 1024-pos, "^n^n\w9. Back");
	pos += format(menu_body[pos], 1024-pos, "^n\w0. Exit");
	show_menu( id,keys,menu_body,-1);

	return PLUGIN_CONTINUE;

}

public do_skillsmenu( id, key )
{
	switch ( key )
	{
		case 0: skills_info( id, 1 );
		case 1: skills_info( id, 2 );
		case 2: skills_info( id, 3 );
		case 3: skills_info( id, 4 );
		case 4: skills_info( id, 5 );
		case 5: skills_info( id, 6 );
		case 6: skills_info( id, 7 );
		case 7: skills_info( id, 8 );
		//case 8: main_menu( id );
		default: return PLUGIN_HANDLED;
	}

	return PLUGIN_HANDLED;

}
