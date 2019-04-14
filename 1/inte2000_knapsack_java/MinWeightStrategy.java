

public class MinWeightStrategy extends Strategy
{
    public MinWeightStrategy() {
        super("Min Weight Strategy");
    }

    int Choose(PackObject[] objs, int c) {
        int index = -1;
        int mw = 10000;
        
        for(int i = 0; i < objs.length; i++) {
            if((objs[i].status == 0) && (objs[i].weight < mw)) {
                mw = objs[i].weight;
                index = i;
            }
        }
        
        return index;
    }
    
}
