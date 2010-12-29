
public InitHud()
{
	hudchat_init();
	hudchat_set_color(255, 255, 255);
	hudchat_set_removetime(1.8);
	hudchat_set_channel(5);
	return;
}

public EndHud()
{
	hudchat_end();
	return;
}

