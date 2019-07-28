    
    template<size_t N>
    class erathostenesSieve
    {
    private:
       std::array<bool,N+1> m_isPrime;
    public:
        constexpr erathostenesSieve() : m_isPrime{}
        {
            for (size_t n = 0; n * n <= N; ++n) m_isPrime[n] = true;
            m_isPrime[0] = false;
            m_isPrime[1] = false;

            for (size_t n = 2; n * n <= N; ++n)
            {
                if (m_isPrime[n])
                {
                    for (size_t multiple = n * n; multiple <= N; multiple += n)
                        m_isPrime[multiple] = false;
                }
            }
        }
        constexpr bool isPrime(size_t n) const noexcept
        {
            return m_isPrime[n];
        }
    };