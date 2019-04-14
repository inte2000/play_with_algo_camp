

public class PriceDensityStrategy extends Strategy
{
    public PriceDensityStrategy() {
        super("Price Density Strategy");
    }

    int Choose(PackObject[] objs, int c) {
        int index = -1 ;
        double ms = 0.0;
        
        for(int i = 0; i < objs.length; i++) {
            if(objs[i].status == 0) {
                double si = objs[i].price;
                si = si / objs[i].weight;
                if(si > ms)
                {
                    ms = si;
                    index = i;
                }
            }
        }
        
        return index;
    }
    
}
