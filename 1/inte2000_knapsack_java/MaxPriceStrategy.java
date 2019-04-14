

public class MaxPriceStrategy extends Strategy
{
    public MaxPriceStrategy() {
        super("Max Price Strategy");
    }

    int Choose(PackObject[] objs, int c) {
        int index = -1 ;
        int mp = 0;
        
        for(int i = 0; i < objs.length; i++) {
            if((objs[i].status == 0) && (objs[i].price > mp)) {
                mp = objs[i].price;
                index = i;
            }
        }
        
        return index;
    }
    
}
