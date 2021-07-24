int attack(int index)
{
    while((Me.hand[index++])!=-1);
    index--;
    
    if(!check_attack(index)){
        printf("your card is not right\n");
        return -1;
    }
    
    int Card=Me.hand[index];
    
    switch (Card) {
        case 52:
            return 9;
            break;
        case 53:
            return 7;
            break;
        default:
            switch(Card%13){
                case 0:
                if((Card/13)==SPDE)
                    return 5;
                return 3;
                case 1:
                    return 2;
                default:
                    return 0;
            }
    }
    
    // A=0(3), 2=1(2), Joker=52,53
    
}

void defend()
{
    // A, 2, 3, Joker
}


int check_attack(int index){
    int card=Me.hand[index];
    int test_card=stack[ind];
    
    if(card>=52)
        return 1;
    if(card%13==test_card%13||card/13==test_card/13)
        return 1;
    return 0;
    
}
